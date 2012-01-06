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


#include <ldc/types.h>
#include <ldc/string.h>


struct info_tuple *new_info_tuple(char *key, char *value)
{
	struct info_tuple *info;
	info = calloc(1, sizeof(struct info_tuple));

	if (key == NULL)
		key = "NULL";

	if (value == NULL)
		value = "NULL";

	info->key = get_clone(key);
	info->value = get_clone(value);

	info->next = NULL;

	return info;
}

char *get_info_tuple_key(struct info_tuple *info)
{
	return info->key;
}

char *get_info_tuple_value(struct info_tuple *info)
{
	return info->value;
}

void free_info_tuple_key_and_value(struct info_tuple *info)
{
	if (info == NULL)
		return;

	if (info->key != NULL)
		delete(&(info->key));

	if (info->value != NULL)
		delete(&(info->value));
}

void free_info_tuple(struct info_tuple **info)
{
	if (*info == NULL)
		return;

	struct info_tuple *next = (*info)->next;
	free_info_tuple(&next);

	free_info_tuple_key_and_value(*info);

	free(*info);
	*info = NULL;
}

void append_info_tuple(struct info_tuple *head, struct info_tuple *node)
{
	if (head == NULL || node == NULL)
		return;

	append_info_tuple(head->next, node);

	if (head->next == NULL)
		head->next = node;
}

void append_new_info_tuple(struct info_tuple *info, char *key, char *value)
{
	struct info_tuple *tmp = new_info_tuple(key, value);
	append_info_tuple(info, tmp);
}

int info_tuple_has_next(struct info_tuple *info)
{
	if (info->next != NULL)
		return 1;

	return 0;
}

int print_info_tuple_list(struct info_tuple *info)
{
	if (info == NULL)
		return EXIT_FAILURE;

	printf("  %s: %s\n", info->key, info->value);

	print_info_tuple_list(info->next);

	return EXIT_SUCCESS;
}

struct device *new_device(char *name)
{
	struct device *dev;
	dev = calloc(1, sizeof(struct device));

	if (dev == NULL)
		return NULL;

	if (name == NULL)
		name = "UNDEFINED";

	dev->name = get_clone(name);

	dev->info = NULL;
	dev->next = NULL;
	dev->child = NULL;

	return dev;
}

void free_device_fields(struct device *dev)
{
	if (dev != NULL)
		delete(&(dev->name));
}

void free_device(struct device **dev)
{
	if (*dev == NULL)
		return;

	struct device *next = (*dev)->next;
	struct device *child = (*dev)->child;
	struct info_tuple *info = (*dev)->info;

	free_device(&next);
	free_device(&child);
	free_info_tuple(&info);

	free_device_fields(*dev);

	free(*dev);
	*dev = NULL;
}

int device_has_next(struct device *dev)
{
	if (dev->next != NULL)
		return 1;

	return 0;
}

void append_device_node(struct device *head, struct device *node)
{
	if (head == NULL || node == NULL)
		return;

	append_device_node(head->next, node);

	if (head->next == NULL)
		head->next = node;
}

void set_child(struct device *parent, struct device *child)
{
	if (parent == NULL || child == NULL)
		return;

	if (parent->child == NULL)
		parent->child = child;
	else
		append_device_node(parent->child, child);
}

void add_info(struct device *dev, struct info_tuple *info)
{
	if (dev == NULL || info == NULL)
		return;

	if (dev->info == NULL)
		dev->info = info;
	else
		append_info_tuple(dev->info, info);
}

char *get_info_value(struct device *dev, char *key)
{
	if (dev == NULL || key == NULL)
		return NULL;

	struct info_tuple *iter = dev->info;

	while (iter != NULL) {
		if (iter->key != NULL && strcmp(key, iter->key) == 0) {
			char *tmp = get_clone(iter->value);
			return tmp;
		}

		iter = iter->next;
	}

	return NULL;
}

int print_device_list(struct device *dev)
{
	if (dev == NULL)
		return EXIT_FAILURE;

	printf("------%s------\n", dev->name);
	print_info_tuple_list(dev->info);
	print_device_list(dev->child);
	printf("------------\n");

	print_device_list(dev->next);

	return EXIT_SUCCESS;
}
