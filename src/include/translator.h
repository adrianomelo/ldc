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


#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <ldc/hashtable.h>
#include <prefix.h>

#ifdef PREFIX
#define TRANSLATION_FILE STR(PREFIX/share/ldc/pt_BR)
#else
#define TRANSLATION_FILE "/usr/share/ldc/pt_BR"
#endif

hash_table *load_translation();

char *get_translation(hash_table *translation, char *label);

#endif

