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
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include <ldc/errors.h>
#include <ldc/log.h>
#include <ldc/file.h>
#include <ldc/string.h>
#include <ldc/terminal.h>


void write_log(char *kind, char *message)
{
	if (message == NULL)
		return;

	if (kind == NULL)
		kind = "error";

	time_t hora;
	hora = time(NULL);
	char *data = ctime(&hora);
	char *date = calloc(strlen(data), sizeof(char));
	strncpy(date, data, strlen(data) - 1);

	int log_size =
	    strlen(kind) + strlen(message) +
	    strlen(date) /* == 25 */ +4 + 5;
	char *log_str = calloc(log_size, sizeof(char));

	sprintf(log_str, "[%s] [%s] %s\n", date, kind, message);

	write_output(log_str, "/tmp/ldc.log", "a");

	delete(&date);
	delete(&log_str);
}

char *_scanf(char *msg, va_list arguments)
{
	char *dst = calloc(MAX_LOG_SIZE, sizeof(char));
	char *tmp;
	for (tmp = msg; *tmp != '\0'; tmp++) {
		int count = strlen(dst);
		if (*tmp == '%') {
			tmp = tmp + 1;
			char *type = tmp;
			if (*type == 's') {
				char *args = va_arg(arguments, char *);
				if (args != NULL)
					strcat(dst, args);

			} else if (*type == 'd') {
				int argi = va_arg(arguments, int);
				char integer[10];
				sprintf(integer, "%d", argi);
				strcat(dst, integer);
			}
		} else {
			dst[count] = *tmp;
		}
	}
	return dst;
}

void log_warning(char *message, ...)
{
	char *log = NULL;
	va_list arguments;

	va_start(arguments, message);
	log = _scanf(message, arguments);

	va_end(arguments);

	write_log("warning", log);
	delete(&log);
}

void log_error(char *message, ...)
{
	char *log = NULL;
	va_list arguments;

	va_start(arguments, message);
	log = _scanf(message, arguments);

	va_end(arguments);

	write_log("error", log);
	delete(&log);
}

void log_debug(char *message, ...)
{
	char *log = NULL;
	va_list arguments;

	va_start(arguments, message);
	log = _scanf(message, arguments);

	va_end(arguments);

	write_log("debug", log);
	delete(&log);
}

void log_known_error(int code)
{
	if (code == SUCCESS)
		return;

	switch (code) {
	case ERROR:
		log_error("Ocorreu um erro não especificado");
		break;
	case DL_SYM_ERROR:
		log_error("Erro ao mapear função do plugin");
		break;
	case CLOSE_STREAM_ERR:
		log_error("Erro ao fechar stream");
		break;
	case CMD_DOESNT_EXIST:
		log_error("Comando de terminal inválido");
		break;
	case THREAD_ERROR:
		log_error("Problemas na criação de threads");
		break;
	case NOT_ROOT_ERROR:
		log_error("É necessário ter privilegio de root para obter as informações do plugin");
		break;
	default:
		log_error("Ocorreu um erro desconhecido");
		break;
	}
}
