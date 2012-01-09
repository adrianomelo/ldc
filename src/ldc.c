/* 
 * 	
 * This file is part of LDC.
 *
 * LDC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LDC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LDC.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// bibliotecas para multi-processo
#include <unistd.h>
#include <sys/types.h> //pid_t
#include <sys/wait.h>
#include <sys/ipc.h>
#include <signal.h>
//#include <asm/signal.h>
//#include <sys/shm.h>
#include <errno.h>

#include <arguments.h>
#include <filelist.h>
#include <libraries.h>
#include <device2xml.h>

#include <ldc/hashtable.h>
#include <ldc/types.h>
#include <ldc/errors.h>
#include <ldc/string.h>
#include <ldc/log.h>
#include <ldc/config.h>
#include <ldc/system.h>

#define WAIT_TIME 20000000
#define INTERVAL 20000

int wait_child_process(pid_t pid, unsigned int microseconds, unsigned int total_time);

int main (int argc, char *argv[])
{
	log_debug ("Execução do LDC iniciada.");

	if (!is_root())
		log_debug("LDC executado sem permissão de root.");


	hash_table *table = new_hash_table();

	int status_opt = load_options(table, argc, argv);
	if (status_opt == ERROR) {
		free_hash_table(&table);
		exit(EXIT_FAILURE);
	}

	load_config (table, CONFIG_FILE);

	informations = new_device ("computer");

	char folder[] = PLUGINS_DIR;
	struct file_list *filelist = NULL;
	if (list_plugins (folder, &filelist) != 0)
		return ERROR;
	
	struct file_list *file = filelist;

	char *single = get_hash_info(table, "single");
	int multi_process = (int) ( single == NULL || equals(single,"no") );
	delete(&single);

	char *only_plugin = get_hash_info(table,"only");
	int only = is_blank(only_plugin) != 1;
	
	pid_t pid;

	while (file != NULL) {
		char filename[250];
		sprintf(filename, "%s%s", PLUGINS_DIR, file->filename);

		char *name = get_plugin_name(filename);
		
		if (name != NULL) {
			char *device_str = get_hash_info (table, name);
			if ((equals(device_str, "no") != 1 && only != 1)
					|| (only == 1 && equals(only_plugin,name)) ) {

				pid = -1;

				if (multi_process == 1){
					pid = fork();
					
					// não conseguiu dar o fork. vai para o próximo plugin
					if (pid < 0)
						continue;
				}

				// não é multiprocesso ou é o processo filho
				if (multi_process == 0 || (multi_process == 1 && pid == 0)) {
					struct device *device = new_device (name);
					int status = open_plugin(device, filename, table);

					if (status == SUCCESS) {
						set_child (informations, device);
					} else {
						free_device (&device);
					}
				}

				if (pid > 0) { // processo pai
					int status;
					status = wait_child_process(pid, (unsigned int) INTERVAL, (unsigned int) WAIT_TIME);
					
					switch (status) {
					case -1:
						log_debug("Não foi possível obter status do plugin.");
						break;
					case -2:
						log_error("Plugin não conseguiu inventariar em tempo hábil.");
						kill(pid, 9); // SIGKILL
						break;
					case 11: // SIGSEGV
						log_error("SIGSEGV recebido durante a execução do plugin (segmentation fault).");
						break;
					case 9: //SIGKILL
						log_error("SIGKILL recebido durante a execução do plugin (processo cancelado).");
						break;
					case 6: // SIGABRT
						log_error("SIGABRT recebido durante a execução do plugin (processo abortado).");
						break;
					}
				} else if (pid == 0) {
					break; // sair do while
				}

			}
			delete(&device_str);
		}

		delete (&name);

		file = file->next;
	}

	if (multi_process == 1) {
		if (pid == 0 && informations->child != NULL)
			device2xml (informations->child, table);
	} else {
		device2xml (informations, table);
	}


	char *print = get_hash_info(table, "print_output");
	if (!equals(print, "no")) {
		if (multi_process == 1) {
			if (pid == 0) {
				print_device_list (informations->child);
			}
		} else {
			print_device_list (informations);
		}
	}
	delete (&print);

	delete (&only_plugin);

	free_hash_table (&table);

	free_device (&informations);
	free_file_list (&filelist);

	if (!multi_process || pid != 0)
		log_debug ("Execução do LDC finalizada.\n");

	return SUCCESS;
}

int wait_child_process(pid_t pid, unsigned int microseconds, unsigned int total_time)
{
	int status;
	pid_t end_pid;
	unsigned int i;
	
	for (i = 0; i < total_time; i+=microseconds) {
		usleep(microseconds);
		//pega o status do processo filho
		end_pid = waitpid(pid, &status, WNOHANG);

		if (end_pid == pid) {
			break;
		}
	}
	
	if (end_pid == 0)
		return -2;
	
	if (end_pid == pid && WIFEXITED(status)) {
		// plugin executou corretamente
		return 0;
	} else if (WIFSIGNALED(status)) {
		return WTERMSIG(status);
	
	} else {
		return -1;
	}
}

