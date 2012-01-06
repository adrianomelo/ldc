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
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <ldc/errors.h>
#include <ldc/file.h>
#include <ldc/log.h>
#include <ldc/string.h>
#include <ldc/lockfile.h>

int write_output(char *string, char *file, char *mode)
{
	if (string == NULL || file == NULL || mode == NULL)
		return ERROR;

	if (strlen(mode) != 1)
		mode = "a";

	if (strcmp(mode, "a") != 0 && strcmp(mode, "w") != 0)
		return ERROR;

	int fd;
	int status;

	mode_t permissions = S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR;

	if (equals(mode, "a"))
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, permissions);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,  permissions);

	status = lock_file(fd);

	if (status == ERROR) {
		close(fd);
		return ERROR;
	}

	status = write(fd, string, strlen(string));

	if (status == -1) {
		unlock_file(fd);
		close(fd);
		return ERROR;
	}

	unlock_file(fd);

	close(fd);
	return SUCCESS;
}

