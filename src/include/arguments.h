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


/** @file arguments.h
 *  @brief Header file contendo funções para fazer o carregamento das opções.
 *
 * Este arquivo contém funções para fazer o carregamento das opções		\n
 * espeficicadas no terminal. 							\n
 *										\n
 * @see ldc --help								\n
 */

#ifndef LDC_ARGUMENTS_H
#define LDC_ARGUMENTS_H

#include <ldc/hashtable.h>

/**
 * Obtem as opções passadas como parâmetro e insere na hash_table.
 * Função que recebe uma hash_table e adiciona a ela as opções especificadas	\n
 * na execução do LDC.								\n
 *										\n
 * @param table hash_table *, Estrutura onde serão adicionadas as opções.	\n
 * @param argc int, um Inteiro contendo a quantidade de argumentos.		\n
 * @param argv char **, um array de strings, contendo as opções passadas.	\n
 *										\n
 * @return um Inteiro que pode ser:						\n
 * 	       - SUCCESS : quando as opções são adicionadas a hash_table.	\n	
 * 	       - ERROR : quando alguma da opções é inválida.			\n
 */
int load_options(hash_table *table, int argc, char *argv[]);

/**
 * Imprime uma mensagem de ajuda para execução do ldc.
 * Função que imprime uma mensagem de ajuda para execução do ldc.		\n
 * Esta função é chamada quando o usuário digina 'ldc -h'.			\n
 */
void print_help();

/**
 * Imprime a versão do LDC.
 * Função que imprime a versão do LDC.						\n
 * Esta função é chamada quando o usuário digina 'ldc -v'.			\n
 */
void print_version();

/**
 * Imprime uma mensagem de erro nas opções do LDC.
 * Função que imprime uma mensagem de erro, caso o usuário passe alguma opção	\n
 * inválida para o LDC (opção inválida ou com falta de argumento).		\n
 */
void print_syntax_error();

/**
 *
 * Verifica se o nome de um plugin é válido.
 * Função que recebe um nome de um plugin e verifica se ele é ou não válido.	\n
 *										\n
 * @param name char *, uma string contendo o nome do plugin a ser validado.	\n
 *										\n
 * @return um Inteiro que pode ser:						\n
 * 	       - 1 : plugin válido.						\n	
 * 	       - 0 : plugin inválido.						\n
 *										\n
 * @todo implementar o retorno desta informação baseada nas pastas do LDC.	\n
 */
int is_valid_plugin(char *name);

void print_fun();
#endif
