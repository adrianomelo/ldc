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

#include <ldc/dmidecode.h>
#include <ldc/terminal.h>
#include <ldc/string.h>
#include <ldc/errors.h>
#include <ldc/system.h>


char *get_dmidecode_output(const int dmi_type, const char *filter,
			   const int line, const int begin)
{
	if (dmi_type < 0 || dmi_type > 23)
		return get_undefined_info();

	if (filter == NULL || line <= 0 || begin <= 0)
		return get_undefined_info();
	
	if (!is_root())
		return get_undefined_info();

	char *dmidecode_path = which("dmidecode");
	if (dmidecode_path == NULL)
		return get_unexistent_dependence();

	char buffer[MAX_DMI_COMMAND_SIZE];

	sprintf(buffer,
		"%s -t %d | grep '%s' | sed '%dq;d' | "
		"awk '{ for(i = %d;i <= NF; i++){printf( $i \" \")}}'",
		dmidecode_path, dmi_type, filter, line, begin);

	delete(&dmidecode_path);

	char *output = get_cmd_output(buffer, MAX_DMI_OUTPUT_SIZE);

	if (output == NULL)
		output = get_undefined_info();

	return output;
}

char *get_dmidecode_keyword_output(const char *keyword, const int line)
{
	if (!is_valid_keyword(keyword) || line <= 0)
		return get_undefined_info();

	if (!is_root())
		return get_undefined_info();

	char *dmidecode_path = which("dmidecode");
	if (dmidecode_path == NULL)
		return get_unexistent_dependence();

	char buffer[MAX_DMI_COMMAND_SIZE];

	sprintf(buffer,
		"%s --string %s | sed '%dq;d'",
		dmidecode_path, keyword, line);

	delete(&dmidecode_path);

	char *output = get_cmd_output(buffer, MAX_DMI_OUTPUT_SIZE);

	if (output == NULL)
		output = get_undefined_info();

	return output;
}

int get_dmidecode_count(int dmi_type, const char *filter)
{
	if (dmi_type < 0 || filter == NULL)
		return 0;
	
	if (!is_root())
		return 0;

	char *dmidecode_path = which("dmidecode");
	
	if (dmidecode_path == NULL)
		return 0;

	int count = 0;

	char buffer[MAX_DMI_OUTPUT_SIZE];

	sprintf(buffer, "%s -t %d | grep \'%s\' | wc -l | awk '{ print $1 }'",
		dmidecode_path, dmi_type, filter);

	delete(&dmidecode_path);

	char *output = get_cmd_output(buffer, MAX_DMI_OUTPUT_COUNT_SIZE);

	if (output != NULL && strcmp(output, UNDEFINED_INFO) != 0
	    && strcmp(output, UNEXISTENT_DEPENDENCE) != 0)
		count = atoi(output);

	delete(&output);
	return count;
}

int is_valid_keyword(const char *keyword)
{
	if (keyword == NULL)
		return 0;

	char *valid_keywords[] = {
		"bios-vendor",
		"bios-version",
		"bios-release-date",
		"system-manufacturer",
		"system-product-name",
		"system-version",
		"system-serial-number",
		"system-uuid",
		"baseboard-manufacturer",
		"baseboard-product-name",
		"baseboard-version",
		"baseboard-serial-number",
		"baseboard-asset-tag",
		"chassis-manufacturer",
		"chassis-type",
		"chassis-version",
		"chassis-serial-number",
		"chassis-asset-tag",
		"processor-family",
		"processor-manufacturer",
		"processor-version",
		"processor-frequency"
	};

	int i = 0;
	int valid = 0;
	while (i < 22 && valid == 0) {
		if (strcmp(keyword, valid_keywords[i]) == 0)
			valid = 1;
		i++;
	}
	return valid;
}
