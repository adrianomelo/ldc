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


/** @file errors.h
 *  @brief Header file correspondente aos erros.
 *
 * O errors.h tem por objetivo centralizar todas as mensagens de erro 	\n
 * do LDC, assim como definir constantes para representar cada erro 	\n
 * tornando simples a alteração de mensagens de erro.\n
 * Também são definidas funções de erro.\n\n
 *
 * @todo definir as funções abaixo em erros.h e erros.c para o log de erros.\n
 * - void error_die (int code, char* message);\n
 * - void error_warning (int code, char* message);\n 
 */

#ifndef ERRORS_H
#define ERRORS_H

/**
 * Obtém UNDEFINED_INFO alocado dinamicamente.
 * Função que retorna um char * alocado dinamicamente, sendo o\n
 * conteúdo a constante UNDEFINED_INFO.\n
 * @return char * UNDEFINED_INFO alocado dinamicamente.
 */
char *get_undefined_info();

/**
 * Obtém UNEXISTENT_DEPENDENCE alocado dinamicamente.
 * Função que retorna um char * alocado dinamicamente, sendo o\n
 * conteúdo a constante UNEXISTENT_DEPENDENCE.\n
 * @return char * UNEXISTENT_DEPENDENCE alocado dinamicamente.
 */
char *get_unexistent_dependence();

/**
 * Constante que define a saída padrão quando a informação\n
 * está ausente, ou quando não é possível obter a mesma.\n
 */
#define UNDEFINED_INFO	"Undefined Information"

/**
 * Constante que define a saída padrão quando a fonte da\n
 * informação, a dependência, não está presente.\n
 */
#define UNEXISTENT_DEPENDENCE	"Undefined Information"

/**
 * Retorno de uma função que foi executada com sucesso.\n
 * Usada em todos os plugins, na função:\n
 * - int get_info(struct device *dev)\n
*/
#define SUCCESS 0

/**
 * Retorno de uma função que não foi executada com sucesso.\n
 * Usada em todos os plugins, na função:\n
 * - int get_info(struct device *dev)\n
*/
#define ERROR -1

/**
 * Erro ao mapear uma função com dlsym (usando o dlopen)
 */
#define DL_SYM_ERROR 20

/**
 * Constante que define o erro a ser retornado quando\n
 * acontece erro ao se fechar uma stream.\n
 */
#define CLOSE_STREAM_ERR 55

/**
 * Constante que define o erro a ser retornado quando um\n
 * comando no terminal é inválido (inexistente).\n
 * Erro identificado ao se fechar a stream com a saída do\n
 * comando.\n
 */
#define CMD_DOESNT_EXIST 58

/**
 * Constante que define o erro a ser retornado quando\n
 * houver problemas na criação de threads.
 */
#define THREAD_ERROR -333

/**
 * Constante que define o erro a ser retornado quando\n
 * não há privilégios de root.
 */
#define NOT_ROOT_ERROR -123

#endif
