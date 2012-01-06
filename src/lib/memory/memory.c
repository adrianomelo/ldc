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


#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ldc/terminal.h>
#include <ldc/dmidecode.h>
#include <ldc/types.h>
#include <ldc/errors.h>
#include <ldc/string.h>
#include <ldc/system.h>
#include <ldc/info.h>

void load_memory_physical_devices(struct device *memory);

int get_info(struct device *device)
{
	if (device == NULL)
		return ERROR;

	set_memory(device);
	return SUCCESS;
}

/**
 * Esta função apenas chama outra função, foi feita separadamente
 * para caso se deseje adicionar informações sobre outros fatores
 * de memória, semelhante a como era feito antes da eliminação de
 * informações do /proc/meminfo, no caso, existia uma função
 * void load_memory_general_information(struct device *memory);
 */
void set_memory(struct device *memory)
{
	load_memory_physical_devices(memory);
}

/************************** <CONTROLLER> ******************************/
struct info_tuple *get_maximum_memory_module_size()
{
	char *information = get_dmidecode_output(MEMORY_CONTROLLER, "Maximum Memory Module Size:", FIRST_LINE, 5);
	struct info_tuple *temp = new_info_tuple("Maximum Memory Module Size", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_maximum_memory_total_size()
{
	char *information = get_dmidecode_output(MEMORY_CONTROLLER, "Maximum Total Memory Size:", FIRST_LINE, 5);
	struct info_tuple *temp = new_info_tuple("Maximum Total Memory Size", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_memory_module_voltage()
{
	char *information = get_dmidecode_output(MEMORY_CONTROLLER, "Memory Module Voltage:", FIRST_LINE, 4);
	struct info_tuple *temp = new_info_tuple("Voltage", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_associated_memory_slots_number()
{
	char *information = get_dmidecode_output(MEMORY_CONTROLLER, "Associated Memory Slots:", FIRST_LINE, 4);
	struct info_tuple *temp = new_info_tuple("Slots", information);
	delete(&information);
	return temp;
}

/************************** </CONTROLLER> ******************************/

/************************** <DEVICE> **********************************/
void load_memory_physical_devices(struct device *memory)
{
	if (memory == NULL)
		return;

	int devices_count = get_total_memory_physical_devices();

	int i;
	for (i = 0; i < devices_count; i++) {
		if (is_memory_device_installed(i)) {
			struct device *mem_device =
			    get_memory_physical_device(i);
			set_child(memory, mem_device);
		}
	}

	//pegar apenas 1 modulo para dar exemplo de saída
	if (devices_count == 0)
		set_child(memory, get_memory_physical_device(0));

}

struct device *get_memory_physical_device(int i)
{
	char device_name[20];
	sprintf(device_name, "Memory %i", i);

	struct device *dev = new_device(device_name);

	add_info(dev, get_memory_device_manufacturer(i));
	add_info(dev, get_memory_device_factor(i));
	add_info(dev, get_memory_device_type(i));
	add_info(dev, get_memory_device_type_detail(i));
	add_info(dev, get_memory_device_size(i));
	add_info(dev, get_memory_device_serial(i));
	add_info(dev, get_memory_device_speed(i));

	add_info(dev, get_maximum_memory_total_size());
	add_info(dev, get_maximum_memory_module_size());
	add_info(dev, get_associated_memory_slots_number());
	add_info(dev, get_memory_module_voltage());

	return dev;
}

struct info_tuple *get_memory_device_manufacturer(int i)
{
	char *information = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Manufacturer:", (i + 1), 2);
	struct info_tuple *temp = new_info_tuple("Vendor", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_memory_device_factor(int i)
{
	char *information = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Form Factor:", (i + 1), 3);
	struct info_tuple *temp = new_info_tuple("Form Factor", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_memory_device_type(int i)
{
	char *information = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Type:", (i + 1), 2);
	struct info_tuple *temp = new_info_tuple("Type", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_memory_device_type_detail(int i)
{
	char *information = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Type Detail:", (i + 1), 3);
	struct info_tuple *temp = new_info_tuple("Type Detail", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_memory_device_size(int i)
{
	char *information = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Size:", (i + 1), 2);
	struct info_tuple *temp = new_info_tuple("Size", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_memory_device_serial(int i)
{
	char *information = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Serial Number:", (i + 1), 3);
	struct info_tuple *temp = new_info_tuple("Serial Number", information);
	delete(&information);
	return temp;
}

struct info_tuple *get_memory_device_speed(int i)
{
	char *information = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Speed:", (i + 1), 2);
	struct info_tuple *temp = new_info_tuple("Speed", information);
	delete(&information);
	return temp;
}

int get_total_memory_physical_devices()
{
	return get_dmidecode_count(MEMORY_PHYSICAL_DEVICE, "^Handle");
}

int is_memory_device_installed(int i)
{
	int is_installed = 1;

	char *output = get_dmidecode_output(MEMORY_PHYSICAL_DEVICE, "Size:", (i + 1), 2);
	
	if (output != NULL && strcmp(output, "No Module Installed") == 0)
		is_installed = 0;

	delete(&output);
	return is_installed;
}
