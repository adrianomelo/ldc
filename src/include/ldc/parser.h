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


/** @file parse.h
 * Este arquivo contém funções para para manipular linhas de arquivo	\n
 * referentes a atribuição, headers entre outros.			\n
 *
 * Para auxiliar na manipulação desses atributos, usa-se a estrutura:	\n
 *	- struct tuple: contém uma key e um value.			\n
 */

#ifndef PARSE_H
#define PARSE_H


/**
 * Estrutura que representa uma atribuição.
 *
 * É uma tupla que representa uma atribuição, que indica a correspondência	\n
 * de uma key com um value.							\n
 * Na atribuição 'a=b', 'a' seria a key, e 'b' o value.				\n
 * Possui os campos:								\n
 * 	- key: representa a chave da atribuição;				\n
 * 	- value: representa o valor atribuido para a key;			\n
 */
struct tuple {
	char *key;
	char *value;
};

/**
 * Função que aloca memória para uma tuple.
 *
 * A função aloca memória para uma tuple e a inicializa, setando os valores	\n
 * passados como parâmetro como key e value da tupla a ser retornada.		\n
 *
 * OBS.: Os parâmetros têm seus valores copiados. Variáveis usadas \n
 * como parâmetros devem ser desalocadas por quem chamar a função.
 *
 * @param key Ponteiro de char (string) da chave;
 * @param value Ponteiro de char (string) que aponta para o valor;
 * @return Ponteiro para a tuple criada;
 */
struct tuple *new_tuple (char *key, char *value);

/**
 * Função que desaloca memória de uma tuple e seu ponteiro.
 *
 * A função libera a tuple e depois libera o ponteiro, não podendo ele ser usado\n
 * novamente.									\n
 *
 * @param tuple Endereço do ponteiro da tuple a ser liberada.			\n
 */
void free_tuple (struct tuple **tuple);

/**
 * Função que recebe uma string de atrubuição e retorna uma tupla.		\n
 * A função recebe uma string do tipo 'a=b' e retorna uma tupla com key 'a' e	\n
 * value 'b'. Caso a string não seja uma atribuição válida, a função retorna	\n
 * NULL.									\n
 *
 * @param string char * contendo uma atribuição do tipo 'abc=qyui';		\n
 * @return Ponteiro para tuple contendo a atribuição ou NULL, caso a atribuição	\n
 *		seja inválida;							\n
 */
struct tuple *parse_tuple (char *string);

/**
 * Função que recebe uma string e retorna a parte dela que bate com o padrão especificado.
 * A função recebe uma expressão regular e uma string, e retorna a parte da string que obedece	\n
 * ao padrão especificado. Caso nenhuma parte da string corresponda ao padrão, esta função irá	\n
 * retornar NULL.										\n
 * value 'b'. Caso a string não seja uma atribuição válida, a função retorna	\n
 * NULL.									\n
 *
 * @param string char * contendo uma atribuição do tipo 'abc=qyui';		\n
 * @return Ponteiro para tuple contendo a atribuição ou NULL, caso a atribuição	\n
 *		seja inválida;
 */
char *re_find (char *pattern, char *string);

#endif

