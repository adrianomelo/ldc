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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <ldc/string.h>
#include <ldc/errors.h>
#include <ldc/terminal.h>


void delete(char **ptr)
{
	if (*ptr == NULL)
		return;

	free(*ptr);
	*ptr = NULL;
}

int is_blank(const char *string)
{
	if (string == NULL || strcmp(string, "") == 0)
		return 1;

	int i;
	for (i = 0; i < strlen(string); i++) {
		char letter = string[i];

		/* o caracter 1 na primeira posição da string
		 * indica que memoria foi alocada(malloc) mas contêm lixo */
		if (letter != ' ' && letter != 1)
			return 0;
	}

	return 1;
}

char *copy_string(char *dst, const char *src, size_t num)
{
	if (dst == NULL || src == NULL || num < 1)
		return NULL;

	strncpy(dst, src, num - 1);

	dst[num - 1] = '\0';
	return dst;
}

char *strip_end(char *str, const char *filter)
{
	if (str == NULL)
		return NULL;
	else if (strlen(str) < 1)
		return get_clone(str);

	int i;

	/* varrendo a string de trás pra frente */
	for (i = strlen(str) - 1; i >= 0; --i) {
		if (!isspace(str[i])) {
			if (filter == NULL) {
				break;
			} else {
				/* se o caracter não for 'space' e
				 * tambem nao estiver no filtro: PARE */
				if (strchr(filter, str[i]) == NULL)
					break;
			}
		}
	}

	char *copy = (char *)calloc(i + 2, sizeof(char));
	strncpy(copy, str, i + 1);
	copy[i + 1] = '\0';

	return copy;
}

int append_string(char **destination, char *string)
{
	if (*destination == NULL && string == NULL)
		return ERROR;

	char *tmp = NULL;

	if (*destination == NULL) {
		size_t tmp_size = strlen(string) + 1;
		tmp = calloc(tmp_size, sizeof(char));
		copy_string(tmp, string, tmp_size);

		*destination = tmp;

		return SUCCESS;
	}

	if (string == NULL)
		return SUCCESS;

	int total_size = strlen(*destination) + strlen(string) + 1;

	tmp = calloc(total_size, sizeof(char));
	strcpy(tmp, *destination);

	char *string_end = tmp + strlen(*destination);
	strcpy(string_end, string);

	delete(destination);
	*destination = tmp;

	return SUCCESS;
}

char *get_clean_string(char *src, char *remove)
{
	if (is_blank(src) || is_blank(remove) || strlen(src) < strlen(remove))
		return NULL;

	char *temp = calloc(strlen(src) + 1, sizeof(char));
	copy_string(temp, src, strlen(src) + 1);

	if (remove_substring(&temp, remove) == ERROR)
		return NULL;

	char *replace = calloc(strlen(temp) + 1, sizeof(char));
	copy_string(replace, temp, strlen(temp) + 1);
	delete(&temp);
	return replace;

}

int remove_substring(char **src, char *remove)
{
	if (*src == NULL || remove == NULL
            || strlen(remove) < 1 || strlen(*src) < strlen(remove))
		return ERROR;

	int rem_size = strlen(remove);

	char *temp_src = *src;
	char *temp_dst = *src;

	while (*temp_src != '\0') {
		if (strncmp(temp_src, remove, rem_size) == 0) {
			temp_src = temp_src + rem_size;
		} else {
			*temp_dst = *temp_src;
			temp_dst++;
			temp_src++;
		}
	}
	*temp_dst = '\0';
	return SUCCESS;
}

char *bytes_to_string(void *bytes, int ini, int end)
{
	if (bytes == NULL || ini < 0 || end < 0)
		return NULL;

	if (ini > end)
		return NULL;

	int string_size = end - ini + 1;
	char *string = calloc(string_size + 1, sizeof(char));

	char *it = (char *)bytes;

	int i;
	for (i = ini; i < end + 1; i++)
		string[i - ini] = *(it + i);

	string[string_size] = '\0';

	return string;
}

int equals(char *a, char *b)
{
	if (a == NULL || b == NULL)
		return 0;

	return (strcmp(a, b) == 0);
}

int equalsn(char *a, char *b, int n)
{
	if (n <= 0)
		return (n == 0);

	if (a == NULL || b == NULL)
		return 0;

	if (strlen(a) < n || strlen(b) < n)
		return 0;

	return (strncmp(a, b, n) == 0);
}

char *get_clone(char *src)
{
	if (src == NULL)
		return NULL;

	int clone_size = strlen(src) + 1;
	char *clone = calloc(clone_size, sizeof(char));
	copy_string(clone, src, clone_size);

	return clone;
}

/*
 * Função que divide a string em tokens, usando os caracteres presentes nos delimitadores, e retorna o n-ésimo token.
 */
char *get_token(char *str, char *delim, int pos)
{
	if (is_blank(str) || pos < 0)
		return NULL;

	if (delim == NULL || strlen(delim) == 0)
		return get_clone(str);

	char *tmp = get_clone(str); 
	char *tok = strtok(tmp, delim);

	int i = 1;
	while (i <= pos && tok != NULL) {
		tok = strtok(NULL, delim);
		i = i + 1;
	}

	char *ret = get_clone(tok);//if tok==NULL (não existe o iézimo delimitador) irá retornar NULL
	delete(&tmp);
	return ret;
}


