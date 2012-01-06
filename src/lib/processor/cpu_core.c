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


#include <stdlib.h>
#include <string.h>

#include <ldc/terminal.h>
#include <ldc/dmidecode.h>
#include <ldc/types.h>
#include <ldc/errors.h>
#include <ldc/string.h>
#include <ldc/system.h>

#include "cpu_core.h"
#include "cpuinfo.h"


struct device *get_core(int i)
{
	char device_name[10];
	sprintf(device_name, "Core %d", i);
	struct device *core = new_device(device_name);

	add_info(core, get_core_vendor_id(i));
	add_info(core, get_core_cpu_mhz(i));
	add_info(core, get_core_physical_id(i));
	add_info(core, get_core_id(i));
	add_info(core, get_cpu_cores_count(i));
	add_info(core, get_core_features(i));

	return core;
}

struct info_tuple *get_core_vendor_id(int i)
{
	char *information = get_cpu_info_output("vendor_id", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("Vendor ID", information);
	delete(&information);
	return info;
}

struct info_tuple *get_core_cpu_mhz(int i)
{
	char *information = get_cpu_info_output("cpu MHz", (i + 1), 4);
	struct info_tuple *info = new_info_tuple("CPU Frequency(MHz)", information);
	delete(&information);
	return info;
}

struct info_tuple *get_core_physical_id(int i)
{
	char *information = get_core_physical_id_value(i);
	struct info_tuple *info = new_info_tuple("Physical ID", information);	//Alterando esta key, alterar no has_physical_id
	delete(&information);
	return info;
}

struct info_tuple *get_core_id(int i)
{
	char *information = get_cpu_info_output("core id", (i + 1), 4);
	struct info_tuple *info = new_info_tuple("Core ID", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cpu_cores_count(int i)
{
	char *information = get_cpu_info_output("cpu cores", (i + 1), 4);
	struct info_tuple *info = new_info_tuple("CPU Cores", information);
	delete(&information);
	return info;
}

struct info_tuple *get_core_features(int i)
{
	char *information = get_cpu_info_output("flags", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("Features", information);
	delete(&information);
	return info;
}

char *get_core_physical_id_value(int i)
{
	return get_cpu_info_output("physical id", (i + 1), 4);
}

int get_cores_count()
{
	return get_cpu_info_output_count("processor");
}

int has_physical_id(char *physical_id, struct device *core)
{
	if (core == NULL)
		return 0;

	struct info_tuple *temp = core->info;

	while (temp != NULL) {
		if (equals(get_info_tuple_key(temp), "Physical ID")) {
			if (equals(get_info_tuple_value(temp), physical_id))
				return 1;
			else
				return 0;
		}
		temp = temp->next;
	}

	return 0;
}

int get_physical_id_uniq_count()
{
	return get_cpu_info_output_uniq_count("physical id");
}

char *get_physical_id_uniq(int i)
{
	return get_cpu_info_output_uniq("physical id", (i + 1), 4);
}
