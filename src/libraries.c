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

#include <filelist.h>
#include <libraries.h>

#include <ldc/types.h>
#include <ldc/hashtable.h>
#include <ldc/errors.h>
#include <ldc/string.h>
#include <ldc/system.h>
#include <ldc/log.h>

#include <dirent.h>
#include <sys/types.h>

#include <dlfcn.h>

int check_dlsym_status (void *dl_handle);
int dl_get_info (void *dl_handle, struct device *plugin);

int (*get_info) (struct device *);


char *get_plugin_name (char *file)
{
	if (file == NULL)
		return NULL;

	char *slash_ptr = strrchr(file, '/');
	char *dot_ptr   = strchr(file, '.');

	if (slash_ptr == NULL || dot_ptr == NULL)
		return NULL;

	int total_size = dot_ptr - slash_ptr;
	int name_size  = total_size - 7;

	if (total_size < 7 || strncmp(slash_ptr, "/libldc", 7) != 0)
		return NULL;

	char *name_with_dot_so = slash_ptr + 7;

	char *name = calloc (name_size + 1, sizeof(char));

	strncpy(name, name_with_dot_so, name_size);
	name[name_size] = '\0';

	return name;
}

int open_plugin (struct device *plugin, char *file, hash_table *config)
{
	if (informations == NULL)
		return ERROR;

	if (plugin == NULL)
		return ERROR;

	void *dl_handle;

	log_debug ("Carregando plugin %s.", file);
	
	dl_handle = dlopen (file, RTLD_LAZY);
	if (!dl_handle) {
		log_error (dlerror());
		return ERROR;
	}

	int status = dl_get_info (dl_handle, plugin);
		
	if (status == DL_SYM_ERROR) {
		dlclose (dl_handle);
		log_error ("Biblioteca não faz inventário de hardware");
		return ERROR;
	} else if (status != SUCCESS) {
		log_known_error(status);
	}

	dlclose(dl_handle);

	if (status == SUCCESS) {
		log_debug ("Informações do plugin foram carregadas");

		return SUCCESS;
	} else {
		log_error ("Erro ao carregar as informações do plugin");
		
		return ERROR;
	}
}

int check_dlsym_status (void *dl_handle) {
	char *error = NULL;
	error = dlerror();

	if (error != NULL) {
		return DL_SYM_ERROR;
	}

	return SUCCESS;
}

int dl_get_info (void *dl_handle, struct device *plugin)
{
	if (dl_handle == NULL) 
		return ERROR;

	if (plugin == NULL)
		return ERROR;
		
	get_info = dlsym (dl_handle, "get_info");
	
	if (check_dlsym_status(dl_handle) != SUCCESS)
		return DL_SYM_ERROR;

	int status = get_info (plugin);

	return status;
}

int list_plugins (char folder[], struct file_list **file)
{
	DIR *directory = opendir(folder);
	struct dirent *entity;
	struct file_list *filelist = NULL;

	if (directory == NULL)
		return ERROR;
	
	while ((entity = readdir(directory)) != NULL) {
		if (strcmp(entity->d_name, ".") != 0 && 
			strcmp(entity->d_name, "..") != 0)
		{
			int len = strlen(entity->d_name);
			int status = 0;
			if (len > 3) {
				status = status + (entity->d_name[len-3] == '.');
				status = status + (entity->d_name[len-2] == 's');
				status = status + (entity->d_name[len-1] == 'o');
			
				if (status == 3) {
					filelist = new_file_list();

					if (filelist == NULL)
						return ERROR;

					if (set_file_list_name(filelist, entity->d_name) != SUCCESS){
						free_file_list (&filelist);
						return ERROR;
					}
			
					if (append_file_list (file, filelist) != SUCCESS){
						free_file_list (&filelist);
						return ERROR;
					}
				}
			}
		}
	}

	closedir(directory);

	return SUCCESS;
}

