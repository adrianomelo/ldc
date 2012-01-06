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

#include <processor/processor.h>
#include <processor/cache.h>
#include <processor/cpu_core.h>


/********************************************************** <GENERAL PROCESSOR INFORMATIONS> *****************************************************************/

void set_caches(struct device *processors[], int processors_count);
void set_cores(struct device *processors[], int processors_count);

int get_info(struct device *device)
{
	if (device == NULL)
		return ERROR;

	set_processor_device(device);
	return SUCCESS;
}

void set_processor_device(struct device *device)
{
	if (device == NULL)
		return;

	int processors_count = get_processors_count();	//returns at least 1;
	struct device *processors[processors_count];

	int i;
	for (i = 0; i < processors_count; i++) {
		processors[i] = new_device("Processor");
		add_info(processors[i], get_processor_family(i));
		add_info(processors[i], get_processor_version(i));
		add_info(processors[i], get_processor_socket_designation(i));
		add_info(processors[i], get_processor_manufacturer(i));
		add_info(processors[i], get_processor_id(i));
		add_info(processors[i], get_processor_voltage(i));
		add_info(processors[i], get_processor_external_clock(i));
		set_child(device, processors[i]);
	}

	set_caches(processors, processors_count);
	set_cores(processors, processors_count);
}

void set_cores(struct device *processors[], int processors_count)
{
	int cores_count = get_cores_count();

	//NO CORES FOUND (add an sample???)
	if (cores_count == 0)
		return;

	if (processors_count == 0)
		return;

	//ONE PROCESSOR (all the cores belongs to him)
	int i;
	if (processors_count == 1) {
		for (i = 0; i < cores_count; i++)
			set_child(processors[0], get_core(i));
		return;
	}
	//INCOMPLATIBLE DMIDECODE and CPUINFO || physical_id_uniq_count == 0
	int physical_id_uniq_count = get_physical_id_uniq_count();
	if (physical_id_uniq_count != processors_count) {
		for (i = 0; i < processors_count; i++)
			set_child(processors[i], get_core(0));
		return;
	}

	char *physical_id[cores_count];
	for (i = 0; i < cores_count; i++) {
		physical_id[i] = get_core_physical_id_value(i);
	}

	for (i = 0; i < processors_count; i++) {
		char *physical_id_uniq = get_physical_id_uniq(i);
		int j;
		for (j = 0; j < cores_count; j++) {
			if (physical_id_uniq && physical_id[j]
			    && strcmp(physical_id_uniq, physical_id[j]) == 0) {
				set_child(processors[i], get_core(j));
			}
		}
		delete(&physical_id_uniq);
	}

	for (i = 0; i < cores_count; i++) {
		delete(&physical_id[i]);
	}
}

void set_caches(struct device *processors[], int processors_count)
{
	int caches_count = get_caches_count();

	int i;
	//NO CACHES, ADD ONE CACHE WITH UNDEFINED_INFO FOR OUTPUT EXAMPLE
	if (caches_count == 0) {
		for (i = 0; i < processors_count; i++)
			set_child(processors[i], get_cache(0));
		return;
	}

	char *handle[caches_count];
	for (i = 0; i < caches_count; i++) {
		handle[i] = get_cache_handle_value(i);
	}

	for (i = 0; i < processors_count; i++) {
		int j;
		char *cache_handle_l1 = get_processor_l1_cache_handle(i);
		char *cache_handle_l2 = get_processor_l2_cache_handle(i);
		char *cache_handle_l3 = get_processor_l3_cache_handle(i);

		for (j = 0; j < caches_count; j++) {
			if (cache_handle_l1 && handle[j]
			    && strcmp(cache_handle_l1, handle[j]) == 0) {
				set_child(processors[i], get_cache(j));
			} else if (cache_handle_l2 && handle[j]
				   && strcmp(cache_handle_l2, handle[j]) == 0) {
				set_child(processors[i], get_cache(j));
			} else if (cache_handle_l3 && handle[j]
				   && strcmp(cache_handle_l3, handle[j]) == 0) {
				set_child(processors[i], get_cache(j));
			}
		}

		delete(&cache_handle_l1);
		delete(&cache_handle_l2);
		delete(&cache_handle_l3);
	}

	for (i = 0; i < caches_count; i++) {
		delete(&handle[i]);
	}
}

struct info_tuple *get_processor_family(int i)
{
	char *information = get_dmidecode_keyword_output("processor-family", (i + 1));
	struct info_tuple *info = new_info_tuple("Family", information);
	delete(&information);
	return info;
}

struct info_tuple *get_processor_version(int i)
{
	char *information = get_dmidecode_keyword_output("processor-version", (i + 1));
	struct info_tuple *info = new_info_tuple("Version", information);
	delete(&information);
	return info;
}

struct info_tuple *get_processor_socket_designation(int i)
{
	char *information = get_dmidecode_output(PROCESSOR, "Socket Designation", FIRST_LINE, 3);
	struct info_tuple *info = new_info_tuple("Socket Designation", information);
	delete(&information);
	return info;
}

struct info_tuple *get_processor_manufacturer(int i)
{
	char *information = get_dmidecode_keyword_output("processor-manufacturer", (i + 1));
	struct info_tuple *info = new_info_tuple("Vendor", information);
	delete(&information);
	return info;
}

struct info_tuple *get_processor_id(int i)
{
	char *information = get_dmidecode_output(PROCESSOR, "ID:", (i + 1), 2);
	struct info_tuple *info = new_info_tuple("ID", information);
	delete(&information);
	return info;
}

struct info_tuple *get_processor_voltage(int i)
{
	char *information = get_dmidecode_output(PROCESSOR, "Voltage:", (i + 1), 2);
	struct info_tuple *info = new_info_tuple("Voltage", information);
	delete(&information);
	return info;
}

struct info_tuple *get_processor_external_clock(int i)
{
	char *information = get_dmidecode_output(PROCESSOR, "External Clock:", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("External Clock", information);
	delete(&information);
	return info;
}

char *get_processor_l1_cache_handle(int i)
{
	char *handler = get_dmidecode_output(PROCESSOR, "L1 Cache Handle:", (i + 1), 4);
	return handler;
}

char *get_processor_l2_cache_handle(int i)
{
	char *handler = get_dmidecode_output(PROCESSOR, "L2 Cache Handle:", (i + 1), 4);
	return handler;
}

char *get_processor_l3_cache_handle(int i)
{
	char *handler = get_dmidecode_output(PROCESSOR, "L3 Cache Handle:", (i + 1), 4);
	return handler;
}

int get_processors_count()
{
	int processors_count = get_dmidecode_count(PROCESSOR, "Processor Information");
	if (processors_count < 1)
		processors_count = 1;

	return processors_count;
}

/********************************************************** <\GENERAL PROCESSOR INFORMATIONS> *****************************************************************/
