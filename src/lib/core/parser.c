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
#include <regex.h>

#include <ldc/string.h>
#include <ldc/parser.h>


struct tuple *new_tuple(char *key, char *value)
{
	if (is_blank(key) || is_blank(value))
		return NULL;

	int key_size = strlen(key);
	int value_size = strlen(value);

	struct tuple *tuple = NULL;
	tuple = malloc(sizeof(struct tuple));

	if (tuple == NULL)
		return NULL;

	tuple->key = NULL;
	tuple->value = NULL;

	tuple->key = calloc(key_size + 1, sizeof(char));
	tuple->value = calloc(value_size + 1, sizeof(char));

	if (tuple->key == NULL || tuple->value == NULL) {
		free_tuple(&tuple);
		return NULL;
	}

	copy_string(tuple->key, key, key_size + 1);
	copy_string(tuple->value, value, value_size + 1);

	return tuple;
}

void free_tuple(struct tuple **tuple)
{
	if (*tuple != NULL) {
		delete(&((*tuple)->key));
		delete(&((*tuple)->value));
		free(*tuple);
		*tuple = NULL;
	}
}

struct tuple *parse_tuple(char *string)
{
	if (is_blank(string))
		return NULL;

	if (string[0] == '#')
		return NULL;

	char *re = re_find(".+=.+", string);

	if (re == NULL)
		return NULL;

	char *key_tmp = re_find(".+=", string);
	char *value_tmp = re_find("=[^\r\n]+", string);

	if (key_tmp == NULL || value_tmp == NULL) {
		delete(&key_tmp);
		delete(&value_tmp);

		return NULL;
	}

	/* tamanho é key_tmp e value_tmp por que tem que remover o '=' das duas strings */
	char *key = calloc(strlen(key_tmp), sizeof(char));
	char *value = calloc(strlen(value_tmp), sizeof(char));

	copy_string(key, key_tmp, strlen(key_tmp));
	copy_string(value, value_tmp + 1, strlen(value_tmp));

	struct tuple *tuple = NULL;

	if (!is_blank(key) && !is_blank(value))
		tuple = new_tuple(key, value);

	delete(&re);
	delete(&key);
	delete(&value);
	delete(&key_tmp);
	delete(&value_tmp);

	return tuple;
}

char *re_find(char *pattern, char *string)
{
	if (pattern == NULL || string == NULL)
		return NULL;

	regex_t re_comp;
	regmatch_t re_match;

	int ret = regcomp(&re_comp, pattern, REG_NEWLINE | REG_EXTENDED);

	if (ret != 0)
		return NULL;

	ret = regexec(&re_comp, string, 1, &re_match, 0);

	if (ret != 0) {
		regfree(&re_comp);
		return NULL;
	}

	char *inicio = string + re_match.rm_so;
	regoff_t tmp_size = re_match.rm_eo - re_match.rm_so;

	char *resultado = calloc(tmp_size + 1, sizeof(char));

	copy_string(resultado, inicio, tmp_size + 1);

	regfree(&re_comp);

	return resultado;
}
