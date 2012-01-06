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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include <ldc/terminal.h>
#include <ldc/errors.h>
#include <ldc/string.h>


char *get_cmd_output(const char *command, size_t buf_size)
{
	if (command == NULL || buf_size < 1)
		return NULL;

	FILE *fp = NULL;
	char *output = NULL;
	char *temp = NULL;
	char *buffer = NULL;
	int status = 0;	

	if ((fp = open_cmd_stream(command)) == NULL)
		return NULL;

	buffer = calloc(buf_size, sizeof(*buffer));

	if (buffer == NULL)
		return NULL;

	if (fgets(buffer, buf_size, fp) != NULL) {
		temp = strip_end(buffer, "");
	}

	delete(&buffer);

	status = close_cmd_stream(&fp);

	if (status == SUCCESS && !is_blank(temp)) {
		output = temp;
	} else {
		delete(&temp);
		output = calloc(100, sizeof(*output));

		if (output == NULL)
			return NULL;

		copy_string(output, UNDEFINED_INFO, 100);
	}
	return output;
}

FILE *open_cmd_stream(const char *command)
{
	if (command == NULL)
		return NULL;

	return popen(command, "r");
}

int close_cmd_stream(FILE **stream)
{
	int status = pclose(*stream);
	*stream = NULL;

	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 127)
			return CMD_DOESNT_EXIST;
		else
			return SUCCESS;
	} else {
		return CLOSE_STREAM_ERR;
	}
}
