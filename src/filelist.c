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
#include <ldc/errors.h>

struct file_list *new_file_list ()
{
	struct file_list *filelist;
	filelist = (struct file_list*) malloc (sizeof(struct file_list));

	if (filelist != NULL)
	{
		filelist->filename = calloc (250, sizeof(char));
		filelist->next = NULL;

		return filelist;
	} else {
		return NULL;
	}
}

int append_file_list (struct file_list **file, struct file_list *filelist)
{
	if (*file == NULL) {
		if (filelist != NULL) {
			*file = filelist;
		} else {
			return ERROR;
		}
	} else {
		struct file_list *next = *file;

		while (next->next != NULL) {
			next = next->next;
		}
		next->next = filelist;
	}

	return SUCCESS;
}

int set_file_list_name (struct file_list *list, char* name)
{
	if (list == NULL)
		return ERROR;

	if (list->filename == NULL)
		return ERROR;

	if (name == NULL)
		return ERROR;

	if (strlen(name) < 250) { 
		strncpy(list->filename, name, strlen(name));
	} else {
		strncpy(list->filename, name, 250);
	}

	return SUCCESS;
}

char *get_file_list_name (struct file_list *list)
{
	if (list == NULL)
		return NULL;

	return list->filename;
}

void free_file_list(struct file_list **list)
{
	if (*list == NULL)
		return;

	if ((*list)->next != NULL)
		free_file_list ( &((*list)->next) );
	
	free((*list)->filename);
	free(*list);
	*list = NULL;
}

