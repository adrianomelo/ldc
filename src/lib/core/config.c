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
#include <string.h>

#include <ldc/log.h>
#include <ldc/errors.h>
#include <ldc/string.h>
#include <ldc/terminal.h>
#include <ldc/hashtable.h>
#include <ldc/config.h>

int load_config (hash_table *table, char *config_file)
{
	if (table == NULL)
		return ERROR;

	if (config_file == NULL)
		return ERROR;

	char buffer[200];
	FILE *p_file = fopen(config_file, "r");

	if (p_file == NULL) {
		log_error ("O arquivo /etc/ldc.conf não existe. "
                   "execute o make install na raiz do projeto LDC compilado.");

		return ERROR;
	}

	while (fgets (buffer, 200, p_file) != NULL){
		hash_info *tuple = parse_tuple_to_hash (buffer);

		if (tuple != NULL) {
			add_hash_info(table, tuple->key, tuple->value);
			free_info_tuple(&tuple);	
		}

	}

	fclose (p_file);

	return SUCCESS;
}

hash_info *parse_tuple_to_hash (char *string)
{
	if (string == 0 || strlen(string) < 2 || is_blank(string))
		return NULL;

	/* é um comentário */
	if (string[0] == '#')
		return NULL;

	char *attribution = strchr(string, '=');
	
	/* não é uma atribuicao */
	if (attribution == NULL)
		return NULL;

	size_t size_key = attribution - string;

	char *key = calloc(size_key + 1, sizeof(char));

	if (key == NULL)
		return NULL;

	key = strncpy(key, string, size_key);
	key[size_key] = '\0';

	char *value = strip_end (attribution + 1, "");

	if (value == NULL)
		return NULL;

	hash_info *info = new_hash_info (key, value);

	delete (&key);
	delete (&value);

	return info;
}

