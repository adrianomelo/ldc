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

#include <ldc/terminal.h>
#include <ldc/string.h>
#include <ldc/errors.h>
#include <ldc/system.h>

#include "cpuinfo.h"


char *get_cpu_info_output(const char *filter, int line, int begin)
{
	if (!file_exists("/proc/cpuinfo"))
		return get_unexistent_dependence();

	if (filter == NULL)
		return get_undefined_info();

	if (line <= 0)
		return get_undefined_info();

	if (begin <= 0)
		return get_undefined_info();

	char buffer[MAX_CPU_INFO_COMMAND];
	sprintf(buffer,
		"cat /proc/cpuinfo | grep '%s' | sed '%dq;d' | awk '{ for(i = %d; i <= NF; i++){printf( $i \" \")}}'",
		filter, line, begin);

	char *output = get_cmd_output(buffer, MAX_CPU_INFO_OUTPUT);

	if (output == NULL)
		output = get_undefined_info();

	return output;
}

int get_cpu_info_output_count(const char *filter)
{
	if (!file_exists("/proc/cpuinfo"))
		return 0;	//get_unexistent_dependence();//UNEXISTENT_DEPENDENCE;

	if (filter == NULL)
		return 0;	//get_undefined_info();

	char buffer[MAX_CPU_INFO_COMMAND];
	sprintf(buffer, "cat /proc/cpuinfo | grep '%s' | wc -l", filter);
	char *output = get_cmd_output(buffer, MAX_CPU_INFO_OUTPUT);

	int count;
	if (output == NULL || strcmp(output, UNDEFINED_INFO) == 0
	    || strcmp(output, UNEXISTENT_DEPENDENCE) == 0)
		count = 0;
	else
		count = atoi(output);

	delete(&output);
	return count;
}

char *get_cpu_info_output_uniq(const char *filter, int line, int begin)
{
	if (!file_exists("/proc/cpuinfo"))
		return get_unexistent_dependence();

	if (filter == NULL)
		return get_undefined_info();

	if (line <= 0)
		return get_undefined_info();

	if (begin <= 0)
		return get_undefined_info();

	char buffer[MAX_CPU_INFO_COMMAND];
	sprintf(buffer,	"cat /proc/cpuinfo | grep '%s' | uniq | sed '%dq;d' | awk '{ for(i = %d; i < NF; i++){printf( $i \" \")}}'",
		filter, line, begin);

	char *output = get_cmd_output(buffer, MAX_CPU_INFO_OUTPUT);
	if (output == NULL)
		output = get_undefined_info();

	return output;
}

int get_cpu_info_output_uniq_count(const char *filter)
{
	if (filter == NULL)
		return 0;

	if (!file_exists("/proc/cpuinfo"))
		return 0;	//UNEXISTENT_DEPENDENCE;

	char buffer[MAX_CPU_INFO_COMMAND];
	sprintf(buffer, "cat /proc/cpuinfo | grep '%s' | uniq | wc -l", filter);
	char *output = get_cmd_output(buffer, MAX_CPU_INFO_OUTPUT);
	
	int count;
	if (output == NULL || equals(output, UNDEFINED_INFO) || equals(output, UNEXISTENT_DEPENDENCE))
		count = 0;
	else
		count = atoi(output);

	delete(&output);
	return count;
}
