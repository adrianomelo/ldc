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


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#include <ldc/errors.h>
#include <ldc/hashtable.h>
#include <ldc/string.h>
#include <ldc/types.h>

hash_table *new_hash_table()
{
	struct hsearch_data *hash = NULL;
	hash = (struct hsearch_data *)calloc(1, sizeof(struct hsearch_data));

	if (hash == NULL)
		return NULL;

	int status = hcreate_r(MAX_HASH_ELEMENTS, hash);

	if (status == 0) {
		if (hash != NULL)
			hdestroy_r(hash);

		return NULL;
	}

	hash_table *table = (hash_table *) calloc(1, sizeof(hash_table));
	table->list = NULL;
	table->hash = hash;

	return table;
}

void free_hash_table(hash_table **table)
{
	if (*table != NULL) {
		if ((*table)->list != NULL)
			free_info_tuple(&((*table)->list));

		if ((*table)->hash != NULL) {
			hdestroy_r((*table)->hash);
			free((*table)->hash);
		}

		free(*table);
		*table = NULL;
	}
}

int add_hash_info(hash_table *table, char *key, char *value)
{
	if (table == NULL || key == NULL || value == NULL)
		return ERROR;

	char *exist = get_hash_info(table, key);

	if (exist != NULL) {
		delete(&exist);
		return ERROR;
	}
	delete(&exist);

	struct info_tuple *temp = new_info_tuple(key, value);

	ENTRY in, *out;
	in.key = temp->key;
	in.data = temp->value;

	int status = hsearch_r(in, ENTER, &out, table->hash);

	if (status == 0) {
		free_info_tuple(&temp);
		return ERROR;
	} else {
		if (table->list == NULL)
			table->list = temp;
		else
			append_info_tuple(table->list, temp);
	}

	return SUCCESS;
}

char *get_hash_info(hash_table *table, char *key)
{
	if (table == NULL || table->hash == NULL || key == NULL)
		return NULL;

	ENTRY in, *out;
	in.key = key;

	hsearch_r(in, FIND, &out, table->hash);

	if (out == NULL || ((char *)out->data) == NULL)
		return NULL;

	return get_clone((char *)out->data);
}

void print_hash_table(hash_table *table)
{
	if (table != NULL && table->hash != NULL && table->list != NULL)
		print_info_tuple_list(table->list);
}

hash_info *new_hash_info(char *key, char *value)
{
	return new_info_tuple(key, value);
}
