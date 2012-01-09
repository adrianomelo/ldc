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

#include "cache.h"

/********************************************************** <GENERAL CACHE INFORMATIONS> **********************************************************************/

struct device *get_cache(int i)
{
	if (i < 0)
		return NULL;

	char device_name[10];
	sprintf(device_name, "Cache %d", i);
	struct device *cache = new_device(device_name);

	//add_info(cache, get_cache_handle(i));
	add_info(cache, get_cache_socket_designation(i));
	add_info(cache, get_cache_configuration(i));
	add_info(cache, get_cache_operational_mode(i));
	add_info(cache, get_cache_location(i));
	add_info(cache, get_cache_installed_size(i));
	add_info(cache, get_cache_maximum_size(i));
//      add_info(cache, get_cache_supported_sram_types(i));
	add_info(cache, get_cache_installed_sram_type(i));
	add_info(cache, get_cache_speed(i));
	add_info(cache, get_cache_error_correction_type(i));
	add_info(cache, get_cache_system_type(i));
	add_info(cache, get_cache_associativity(i));
	return cache;
}

struct info_tuple *get_cache_handle(int i)
{
	char *information = get_cache_handle_value(i);
	struct info_tuple *info = new_info_tuple("Handle", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_socket_designation(int i)
{
	char *information = get_dmidecode_output(CACHE, "Socket Designation:", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("Socket Designation", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_configuration(int i)
{
	char *information = get_dmidecode_output(CACHE, "Configuration:", (i + 1), 2);
	struct info_tuple *info = new_info_tuple("Configuration", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_operational_mode(int i)
{
	char *information = get_dmidecode_output(CACHE, "Operational Mode:", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("Operational Mode", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_location(int i)
{
	char *information = get_dmidecode_output(CACHE, "Location:", (i + 1), 2);
	struct info_tuple *info = new_info_tuple("Location", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_installed_size(int i)
{
	char *information = get_dmidecode_output(CACHE, "Installed Size:", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("Installed Size", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_maximum_size(int i)
{
	char *information = get_dmidecode_output(CACHE, "Maximum Size:", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("Maximum Size", information);
	delete(&information);
	return info;
}

/*
struct info_tuple *get_cache_supported_sram_types(int i)
{
	char *information = get_dmidecode_output(CACHE, "Supported SRAM Types:", (i + 1), 4);
	struct info_tuple *info = new_info_tuple("Supported SRAM Types", information);
	delete(&information);
	return info;
}
*/

struct info_tuple *get_cache_installed_sram_type(int i)
{
	char *information = get_dmidecode_output(CACHE, "Installed SRAM Type:", (i + 1), 4);
	struct info_tuple *info = new_info_tuple("Installed SRAM Type", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_speed(int i)
{
	char *information = get_dmidecode_output(CACHE, "Speed:", (i + 1), 2);
	struct info_tuple *info = new_info_tuple("Speed", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_error_correction_type(int i)
{
	char *information = get_dmidecode_output(CACHE, "Error Correction Type:", (i + 1), 4);
	struct info_tuple *info = new_info_tuple("Error Correction Type", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_system_type(int i)
{
	char *information = get_dmidecode_output(CACHE, "System Type:", (i + 1), 3);
	struct info_tuple *info = new_info_tuple("System Type", information);
	delete(&information);
	return info;
}

struct info_tuple *get_cache_associativity(int i)
{
	char *information = get_dmidecode_output(CACHE, "Associativity:", (i + 1), 2);
	struct info_tuple *info = new_info_tuple("Associativity", information);
	delete(&information);
	return info;
}

/************************ <GENERAL CACHE AUXILIARES> *******************************/

char *get_cache_handle_value(int i)
{
	if (!is_root())
		return get_undefined_info();	//new_info_tuple("Handle", UNDEFINED_INFO);

	if (i < 0)
		return get_undefined_info();	//new_info_tuple("Handle", UNDEFINED_INFO);

	char *dmidecode_path = which("dmidecode");
	if (dmidecode_path == NULL) {
		return get_unexistent_dependence();	//new_info_tuple("Handle", UNEXISTENT_DEPENDENCE);
	}

	char buffer[MAX_DMI_COMMAND_SIZE];
	sprintf(buffer, "%s -t 7 | grep 'Handle' | sed '%dq;d'  | awk '{printf $2}'",
				dmidecode_path, (i + 1));
	delete(&dmidecode_path);

	char *output = get_cmd_output(buffer, MAX_HANDLE_SIZE);

	if (output == NULL)
		output = get_undefined_info();

	char *information = strip_end(output, ",");
	delete(&output);
	return information;
	/*
	   struct info_tuple *info = new_info_tuple("Handle", information);
	   delete(&information);

	   return info;
	 */
}

int has_cache_handle(char *handle, struct device *cache)
{
	if (cache == NULL)
		return 0;
	struct info_tuple *temp = cache->info;
	while (temp != NULL) {
		if (strcmp(get_info_tuple_key(temp), "Handle") == 0) {
			if (strcmp(get_info_tuple_value(temp), handle) == 0)
				return 1;
			else
				return 0;
		}
		temp = temp->next;
	}
	return 0;
}

int get_caches_count()
{
	return get_dmidecode_count(CACHE, "Cache Information");
}

/************************ <\GENERAL CACHE AUXILIARES> ******************************/
/********************************************************** <\GENERAL CACHE INFORMATIONS> **********************************************************************/
