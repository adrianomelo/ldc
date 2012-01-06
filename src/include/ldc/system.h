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


/** @file system.h
 *  @brief Header file contendo funções para verificar dependências, permissões e existência de arquivos.
 *
 * Este arquivo possui diversas funções para funcionalidades utilizadas por	\n
 * vários plugins.	\n
 * Estas funcionalidades são:	\n
 *	- Verificar existencia de uma dependência
 * 	- Verificar se um arquivo existe
 * 	- Obter o caminho até um binário específico
 * 	- Verificar se a aplicação foi executada por super-usuário\n
 *
 */

#ifndef LDC_SYSTEM_H
#define LDC_SYSTEM_H

/**
 * Constante que define quantos diretórios serão vasculhados pelo which.
 */
#define WHICH_NUM_DIR 7

/**
 * Verifica se uma dependência está instalada ou não.
 * Esta função verifica se uma dependência, como o dmidecode, está
 * instalada ou não. A função retorna 1, caso a dependencia esteja
 * instalada e 0, caso contrário.
 * 
 * @param dependency char *, string contendo o nome da dependência
 *            que se deseja verificar se está instalada.
 * 
 * @return um Inteiro, podendo ser:\n
 *		- 1 : Caso a dependência esteja instalada.
 *		- 0 : Caso a dependência não esteja instalada.\n
 */

int has_dependence(char *dependency);


/**
 * Verifica se um arquivo existe ou não.
 * Esta função verifica se um arquivo, como o /proc/cpuinfo, existe ou não.	\n 
 * A função retorna 1, caso o arquivo existe e 0, caso contrário.		\n
 * 
 * @param file_name char *, string contendo o nome do arquivo	\n
 *            que se deseja verificar a existência.		\n
 * 
 * @return um Inteiro, podendo ser:				\n
 *		- 1 : Caso o arquivo existe.
 *		- 0 : Caso o arquivo não exista.		\n
 */
int file_exists(char* file_name);

/**
 * Retorna o caminho para um determinado binário.
 * Esta função retorna o caminho para um binário específico, como o dmidecode.	\n
 * Caso o binário não seja encontrado, a função retorna NULL.			\n
 * 
 * @see which (esta função é semalhante ao which do unix, ver 'man which')	\n
 *
 * @param program char *, string contendo o nome do programa que se deseja 	\n
 * 	      	obter o caminho completo.					\n
 * 
 * @return char *, uma string contendo o caminho completo para o binário	\n
 * 		especificado no parâmetro ou NULL, caso não seja encontrado.	\n
 */
char *which (char* program);

/**
 * Verifica se a aplicação que chama a função foi executada por um super-usuário.
 * Esta função verifica se a aplicação que chama a função foi executada por um	\n 
 * super-usuário. 								\n
 * 
 * @return um Inteiro, podendo ser:						\n
 *		- 1 : Aplicação executada por super-usuário.
 *		- 0 : Aplicação não executada por super-usuário.\n
 */
int is_root(void);

#endif
