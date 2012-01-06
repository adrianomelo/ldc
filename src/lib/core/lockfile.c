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


#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <ldc/lockfile.h>
#include <ldc/errors.h>


int lock_file(int fd)
{
	if (fd == -1)
		return ERROR;

	struct flock file_locker;
	file_locker.l_type = F_WRLCK;
	file_locker.l_whence = SEEK_SET;
	file_locker.l_start = 0;
	file_locker.l_len = 0; /* lock em todo o arquivo */

	int locked = fcntl(fd, F_SETLKW, &file_locker);

	if (locked == -1)
		return ERROR;

	return SUCCESS;
}

int unlock_file(int fd)
{
	if (fd == -1)
		return ERROR;

	struct flock file_unlocker;
	file_unlocker.l_type = F_UNLCK;
	file_unlocker.l_whence = SEEK_SET;
	file_unlocker.l_start = 0;
	file_unlocker.l_len = 0;

	int unlocked = fcntl(fd, F_SETLK, &file_unlocker);

	if (unlocked == -1)
		return ERROR;

	return SUCCESS;
}
