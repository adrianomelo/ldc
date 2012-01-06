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


/** @file hashtable.h
 *  @brief Header file contendo funções para manipular hash_tables.		\n
 *
 * Este arquivo contém funções para manipular hash_tables. 			\n
 * Estas estruturas são usadas para se ter acesso as configurações 		\n
 * internamente (depois de fazer o carregamento das configurações, as		\n
 * mesmas são gravadas em uma hash_table).					\n
 *
 * @see config.h (uso de hash_table)						\n
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define _GNU_SOURCE

#include <search.h>
#include <ldc/types.h>


/** 
 * Definição do número de elementos máximo de uma hash_table.		\n
 */
#define MAX_HASH_ELEMENTS 1000

/** 
 * Definição da hash_info.	\n
 */
typedef struct info_tuple hash_info;

/** 
 * Definição da hash_table.	\n
 */
struct hash_table
{
	struct info_tuple *list;
	struct hsearch_data *hash;

};
typedef struct hash_table hash_table;

/**
 * Retorna uma hash_info alocada dinamicamente.
 * Função usada para se criar uma hash_info (elemento de uma hash_table). 	\n
 * Ela retorna uma nova hash_info alocada dinamicamente com suas referências	\n
 * e valores internos setados para NULL.					\n
 *
 * @return uma Estrutura, hash_info *, alocada dinamicamente com key e value 	\n
 *             setados para NULL.						\n
 */
hash_table *new_hash_table ();

/**
 * Adiciona um novo elemento (hash_info) com key e value segundo os parâmetros especificados em uma hash_table.
 * Função usada para se inserir um novo elemento (hash_info) em uma hash_table 	\n
 * sem precisar criar a hash_info extenamente.					\n
 *
 * @param table hash_table *, Estrutura onde será adicionado o novo elemento com\n
 *             key e value especificados nos demais parâmetros.			\n
 * @param key char *, string referente a key do novo elemento (hash_info) que 	\n
 *             será inserido na hash_table.					\n
 * @param value char *, string referente ao value do novo elemento (hash_info) 	\n
 *             que será inserido na hash_table.					\n
 *
 * @return int um Inteiro referente ao status da operação, podendo ser ERROR ou \n
 *	       SUCCESS								\n
 */
int add_hash_info (hash_table *table, char *key, char *value);

/**
 * Obtém um value correspondente a key passada como parâmetro em uma hash_table.\n
 * Função usada para se obter um value correspondente a uma key de uma		\n
 * hash_table. A função retorna uma string alocada dinamicamente contendo	\n
 * o value referente a key especificada.					\n
 *
 * @param table hash_table *, Estrutura onde será procurado o value com a key	\n
 *             especificada no parâmetro.					\n
 * @param key char *, string referente a key que será usada para buscar a value	\n
 *             retornada.							\n
 *
 * @return uma string, char *, alocada dinamicamente contendo a value correspondente	\n
 *             a key passada como parâmetro.					\n
 */
char *get_hash_info (hash_table *table, char *key);

/**
 * Libera memória alocada para uma hash_table, assim como para todos os seus elementos.	
 * Função usada para desalocar memória de uma hash_table.			\n
 * Os seus elementos internos são desalocados internamente.			\n
 *
 * @param table hash_table **, Estrutura cuja memória será liberada.		\n
 */
void free_hash_table (hash_table **table);

/**
 * Imprime os elementos de uma hash_table.
 * Função usada para imprimir o conteúdo de uma hash_table.			\n
 * 										\n
 * @param table hash_table *, Estrutura cujo conteúdo será impresso.		\n
 */
void print_hash_table(hash_table *table);

/**
 * Função que aloca memória para uma hash_info.
 *
 * A função aloca memória para uma hash_info e a inicializa, \n
 * setando a chave como key e valor como value. \n
 * \n
 * OBS.: Os parâmetros têm seus valores copiados. Variáveis usadas \n
 * como parâmetros devem ser desalocadas por quem chamar a função.
 *
 * @param key Ponteiro de char (string) da chave
 * @param value Ponteiro de char (string) que aponta para o valor
 * @return Ponteiro para a hash_info criada
 */
hash_info *new_hash_info(char *key, char *value);

#endif

