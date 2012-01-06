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
#include <unistd.h>

#include <ldc/system.h>
#include <ldc/terminal.h>
#include <ldc/string.h>
#include <ldc/errors.h>
#include <ldc/log.h>

int file_exists(char *file_name)
{
	if (access(file_name, F_OK) != -1)
		return 1;
		
	return 0;
}

int is_root()
{
	int is_root = 0;

	char *user = get_cmd_output("whoami", 50);
	if (user != NULL && strcmp(user, "root") == 0)
		is_root = 1;

	delete(&user);
	return is_root;
}

char *which(char *program)
{
	if (program == NULL)
		return NULL;

	char pastas_path[WHICH_NUM_DIR][50] = {
		"/usr/local/ldc/sbin/",
		"/bin/",
		"/sbin/",
		"/usr/bin/",
		"/usr/sbin/",
		"/usr/local/bin/",
		"/usr/local/sbin/"
	};

	char *absolute_program = (char *)malloc(50 * sizeof(char));

	int i = 0;
	while (i < WHICH_NUM_DIR) {
		strcpy(absolute_program, strcat(pastas_path[i], program));

		if (file_exists(absolute_program))
			return absolute_program;

		i++;
	}
	delete(&absolute_program);

	/* LOG para o caso de não achar o programa */
	char *tmp = "O programa '' não foi encontrado.";
	char *erro = calloc(strlen(tmp) + strlen(program) + 1, sizeof(char));
	sprintf(erro, "O programa '%s' não foi encontrado", program);
	log_error(erro);
	delete(&erro);
	/* fim do LOG */

	return NULL;
}

int has_dependence(char *dependency)
{
	char *temp = which(dependency);
	int has_dependence = 1;

	if (temp == NULL)
		has_dependence = 0;

	delete(&temp);
	return has_dependence;
}
