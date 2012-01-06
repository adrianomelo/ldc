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

#include <ldc/errors.h>
#include <ldc/string.h>
#include <ldc/log.h>


char *get_undefined_info()
{
	size_t size = strlen(UNDEFINED_INFO) + 1;
	char *info = calloc(size, sizeof(char));

	copy_string(info, UNDEFINED_INFO, size);

	return info;
}

char *get_unexistent_dependence()
{
	size_t size = strlen(UNEXISTENT_DEPENDENCE) + 1;
	char *info = calloc(size, sizeof(char));

	copy_string(info, UNEXISTENT_DEPENDENCE, size);

	return info;
}

