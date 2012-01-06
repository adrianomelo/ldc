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


#ifndef FILELIST_H
#define FILELIST_H

/** @file filelist.h
 * Arquivos que contém a estrutura file_list e funções para manipulá-la.
 */


/**
 * Estrutura que representa um arquivo ou lista de arquivos.
 *
 * Possui:
 * 	- filename: nome do arquivo
 * 	- next: próximo arquivo da lista
 */
struct file_list
{
	char *filename;
	struct file_list *next;
};

/**
 * Função que aloca memória para uma file_list.
 *
 * A função aloca memória para uma file_list e seu nome, \n
 * retornando o ponteiro para a nova file_list.
 *
 * @return Ponteiro da nova file_list
 */
struct file_list *new_file_list ();

/**
 * Função que adiciona em uma lista de arquivos um outro arquivo ou lista.
 *
 * A função adiciona filelist no final da lista da qual file é a cabeça.
 *
 * @param file Lista de arquivos a receber o novo arquivo ou lista
 * @param filelist arquivo ou lista de arquivos a ser adicionada a outra lista
 */
int append_file_list (struct file_list **file, struct file_list *filelist);

/**
 * Função que seta o nome do arquivo.
 *
 * Bla
 *
 * @param list Arquivo a ter o nome alterado
 * @param name Nome a ser setado no arquivo
 * @return
 * 	- SUCCESS: caso não haja problemas na execução
 * 	- ERROR: caso algum dos parâmetros seja NULL ou nome do \n
 * 				 arquivo não tenha memória alocada
 */
int set_file_list_name (struct file_list *list, char* name);

/**
 * Função que retorna o nome de um arquivos.
 *
 * @param list Arquivo cujo nome deseja-se obter
 * @return
 * 	- NULL, caso o nome do arquivo seja NULL
 * 	- String (char*) com o nome do arquivo, caso contrário
 */
char *get_file_list_name (struct file_list *list);

/**
 * Função que libera memória usada por uma file_list.
 *
 * A função libera memória da file_list, de seu nome e também de seu ponteiro.
 *
 * @param list Endereço do ponteiro que referencia a lista de arquivos
 */
void free_file_list(struct file_list **list);

#endif
