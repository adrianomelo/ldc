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


/** @file string.h
 * Arquivo que contém funções para manipulação de string (char*).
 */

#ifndef LDC_STRING_H
#define LDC_STRING_H

#include <stddef.h>

/**
 * Função que libera memória de uma string.
 * A função desaloca memória para uma string (char*), assim \n
 * como seu ponteiro, tornando-o inutilizável.
 *
 * @param ptr Endereço do ponteiro da string
 */
void delete (char **ptr);

/**
 * Função que verifica se a string (char*) é válida.
 * @param string String (char*) a ser avaliada
 * @return
 * 	- 1: quando a string é NULL ou vazia
 * 	- 0, caso contrário
 */
int is_blank (const char *string);

/**
 * Função que copia de uma string (char*) para outra.
 * A função copia os num primeiros caracteres de src para \n
 * pos num primeiros caracteres de dst.
 *
 * @param dst String (char*) destino
 * @param src String (char*) origem da cópia
 * @param num Número de caracteres a serem copiados
 * @return String (char*) dst depois da cópia.
 */
char *copy_string(char *dst, const char *src, size_t num);

/**
 * Função que elimina caracteres indesejados no final de uma string (char*).
 * A função elimina todos os espaços e caracteres presentes no filtro \n
 * seguidos no fim da string (char*) passada.
 *
 * @param str String (char*) a ter caracteres eliminados
 * @param filter String (char*) que contém todos os caracteres, \n
 * 			além do espaço, que se deseja eliminar.
 * @return String (char*) str depois de ter caracteres eliminados.
 */
char *strip_end(char *str, const char *filter);

/**
 * Função que concatena duas strings (char*).
 *
 * @param destination Endereço da string (char*) a receber a concatenação
 * @param string String (char*) a ser concatenada no final da outra
 * @return Status da operação:
 * 	- ERROR: caso os parâmetros sejam NULL
 * 	- SUCCESS: caso não haja problemas na execução
 */
int append_string (char **destination, char *string);

/**
 * Função que elimina substring.
 * A função elimina ocorrências da string remove em src.			\n
 *
 * @param src String (char*) a ter parte removida				\n
 * @param remove Substring a ser removida					\n
 * @return String (char*) src depois de ter a substring remove eliminada	\n
 */
char *get_clean_string(char *src, char *remove);

/**
 * Função que remove uma substring.
 * A função remove uma dada substring da string passada em **src.		\n
 *
 * @param src Endereço da string (char*) a ter a substring removida.		\n
 * @param remove String (char*) a ser removida					\n
 * @return Status da operação:							\n
 * 	- ERROR: caso algum parâmetro seja NULL ou remove for maior que src	\n
 * 	- SUCCESS: caso não haja problemas na execução				\n
 */
int remove_substring(char **src, char *remove);

/**
 * Função que extrai um char * de um void *.					
 * A função extrai um char * de um void *, iniciando da posição passada		\n
 * como parâmetro em ini, e terminando na posição passada em end.		\n
 *
 * @param bytes void *, array de bytes de onde será extraída a substring.	\n
 * @param ini int correspondente a posição do início do char * a ser extraído.	\n
 * @param end int correspondente a posição do fim do char * a ser extraído.	\n
 *
 * @return char * alocado dinamicamente com a substring espeficicada ou NULL	\n
 * 		em caso de parâmetros inválidos.				\n
 */
char *bytes_to_string(void *bytes, int ini, int end);

/**
 * Função que compara duas strings.
 * A função compara duas strings passadas como parâmetro, e retorna 1, caso as		\n
 * strings sejam iguais ou 0, caso sejam diferentes ou alguma delas seja NULL.		\n
 *
 * @param a String (char *) contendo a string a ser comparada com a segunda string.	\n
 * @param b String (char *) contendo a string a ser comparada com a primeira string.	\n
 *
 * @return int um Inteiro que pode ser:							\n
 * 		- 1 : As strings são iguais;						\n
 * 		- 0 : As strings são diferentes ou pelo menos uma delas é NULL;		\n
 */
int equals(char * a, char *b);

/**
 * Função que compara os N primeiros caracteres de duas strings.				
 * A função compara os N primeiros caracteres das strings passadas como parâmetro,		\n
 * e retorna 1, caso as	strings sejam iguais ou 0, caso sejam diferentes ou alguma 		\n
 * delas seja NULL.										\n
 *
 * @param a String (char *) contendo a string a ser comparada com a segunda string.		\n
 * @param b String (char *) contendo a string a ser comparada com a primeira string.		\n
 *
 * @return int um Inteiro que pode ser:								\n
 * 		- 1 : As strings possuem os primeiros N caracteres iguais;			\n
 * 		- 0 : As N primeiros caracteres são diferentes ou não é possível comparar;	\n
 */
int equalsn(char *a, char *b, int n);

/**
 * Função que retorna uma cópia de uma string.
 * A função copia a string passada como parâmetro, e retorna a cópia. 	\n
 * Caso a string seja NULL, será retornado NULL, caso contrário, será	\n
 * retornado uma string alocada dinamicamente, sendo resposabilidade	\n
 * de quem chama a função, liberar a memória alocada.			\n
 *
 * @param src String (char*) a string a ser copiada.			\n
 * @return String (char*) uma cópia da string alocada dinamicamente.	\n
 */
char *get_clone(char *src);

/**
 * Função que separa string em tokens, de acordo com um \n
 * delimitador, e retorna o n-ésimo token.
 *
 * @param str String (char*) a ser dividida
 * @param delim String (char*) com os caracteres que servem de delimitadores
 * @param pos Número do token desejado, que começa em zero (0)
 * @return String (char*) com o token
 */
char * get_token(char *str, char *delim, int pos);

#endif
