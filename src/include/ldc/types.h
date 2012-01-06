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


/** @file types.h
 * Este arquivo contém estruturas básicas do LDC e funções para manipulá-las.
 *
 * As estruturas são:
 *	- Device: representa um dispositivo ou lista de dispositivos
 * 	- Info_tuple: representa uma informação ou lista de informações
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Estrutura que representa uma tupla de informação do device.
 *
 * É uma tupla que representa as informações de \n
 * um dispositivo, no formato (chave,valor). \n
 * \n
 * Possui os campos:
 * 	- key: representa a chave, o tipo de dado da informação \n
 *		 (por exemplo, "espaço livre em disco" para disco rígido)
 * 	- value: representa o valor da informação
 * 	- next: representa a próxima info_tuple-irmã da lista
 */
struct info_tuple
{
  char *key;
  char *value;
  struct info_tuple *next;
};

/**
 * Função que aloca memória para uma info_tuple.
 *
 * A função aloca memória para uma info_tuple e a inicializa, \n
 * setando a chave como key e valor como value. \n
 * \n
 * OBS.: Os parâmetros têm seus valores copiados. Variáveis usadas \n
 * como parâmetros devem ser desalocadas por quem chamar a função.
 *
 * @param key Ponteiro de char (string) da chave
 * @param value Ponteiro de char (string) que aponta para o valor
 * @return Ponteiro para a info_tuple criada
 */
struct info_tuple *new_info_tuple(char *key, char *value);

/**
 * Função que retorna a chave de uma info_tuple.
 *
 * @param info Info_tuple da qual se deseja saber a chave
 * @return String (char*) com a chave da info_tuple
 */
char *get_info_tuple_key(struct info_tuple *info);

/**
 * Função que retorna o valor de uma info_tuple.
 *
 * @param info Info_tuple da qual se deseja saber o valor
 * @return String (char*) com o valor da info_tuple
 */
char *get_info_tuple_value(struct info_tuple *info);

/**
 * Função que libera memória do valor e da chave da info_tuple.
 *
 * A função desaloca memória da chave e do valor \n
 * da info_tuple, mas não desaloca a info_tuple em si \n
 * nem seu ponteiro para próxima info_tuple na lista.
 *
 * @param info Info_tuple a ter sua chave e seu valor liberados
 */
void free_info_tuple_key_and_value(struct info_tuple *info);

/**
 * Função que desaloca memória de uma info_tuple e seu ponteiro.
 *
 * A função libera a info_tuple e depois libera o ponteiro, \n
 * não podendo ele ser usado novamente.
 *
 * @param info Endereço do ponteiro da info_tuple a ser liberada
 */
void free_info_tuple(struct info_tuple **info);

/**
 * Função que adiciona a info_tuple node ao final da lista \n
 * de info_tuple-irmãs de head.
 *
 * A função adiciona node no final da lista de irmãs da info_tuple head.
 *
 * @param head Info_tuple que representa a cabeça da lista.
 * @param node Info_tuple a ser adicionada na lista.
 */
void append_info_tuple(struct info_tuple *head, struct info_tuple *node);

/**
 * Função que cria e adiciona uma info_tuple ao final \n
 * da lista de info_tuple-irmãs de info.
 * @see append_info_tuple
 *
 * @param info Info_tuple que representa a cabeça da lista.
 * @param key Chave da nova info_tuple a ser adicionada à lista. 
 * @param value Valor da nova info_tuple a ser adicionada à lista. 
 */
void append_new_info_tuple(struct info_tuple *info, char *key, char *value);

/**
 * Função que verifica se uma info_tuple não é a última da lista.\n
 *
 * @param info Info_tuple a ser verificada.
 * @return - 1, se houver uma próxima info_tuple-irmã na lista
 * 	- 0, caso contrário
 */
int info_tuple_has_next(struct info_tuple *info);

/**
 * Função que imprime a lista de info_tuples a partir de info.
 *
 * @param info Cabeça da lista de info_tuples a ser impressa
 * @return Status da operação:
 * 	- EXIT_FAILURE: caso a info_tuple passada seja NULL
 * 	- EXIT_SUCCESS: caso contrário
 */
int print_info_tuple_list(struct info_tuple *info);

/**
 * Estrutura que representa um dispositivo.
 *
 * Formado por:
 * 	- name: nome do device
 * 	- info: cabeça da lista de info_tuples do device
 * 	- next: o próximo device na lista
 * 	- child: cabeça da lista de dispositivos-filhos
 */
struct device
{
  char *name;
  struct info_tuple *info;
  struct device *next;
  struct device *child;
};

/**
 * Função que aloca memória para um device.
 *
 * A função aloca memória para um device \n
 * e o inicializa, setando seu nome e retornando \n
 * um ponteiro para este novo device. \n
 * \n
 * OBS.: Os parâmetros têm seus valores copiados. \n
 * Variáveis usadas como parâmetros devem ser \n
 * desalocadas por quem chamar a função.
 *
 * @param name Nome do device a ser criado.
 * @return Ponteiro para device criado.
 */
struct device *new_device(char *name);

/**
 * Função que libera memória dos campos de um device.
 *
 * A função desaloca o nome do device, mas não desaloca\n
 * o device em si, nem o próximo device da lista.
 *
 * @param dev Device a ter seus campos (name) liberados
 */
void free_device_fields(struct device *dev);

/**
 * Função que libera a memória do device passado como parâmetro,
 * além de todos as estruturas relacionadas à ele. Sendo usada
 * por exemplo para desalocar todos os devices e info_tuples usadas
 * no LDC.
 *
 * @param dev Endereço do ponteiro do device a ser liberado
 */
void free_device(struct device **dev);

/**
 * Função que adiciona um device no final da lista que head
 * encabeça.
 *
 * @param head Device a receber outro device como irmão
 * @param node Device a ser adicionado como irmão do outro
 */
void append_device_node(struct device *head, struct device *node);

/**
 * Função que adiciona child a lista de devices filhos de parent.
 *
 * @param parent Device a receber outro device como filho
 * @param child Device a ser adicionado como filho do outro
 */
void set_child(struct device *parent, struct device *child);

/**
 * Função que adiciona uma info_tuple a um device.
 *
 * @param dev Device a receber a info_tuple
 * @param info Info_tuple a ser adicionada no device
 */
void add_info(struct device *dev, struct info_tuple *info);

/**
 * Função que varre a lista de info_tuples do device passado\n
 * como parâmetro e retorna o valor da info_tuple que possui\n
 * chave igual a key.
 *
 * @param dev Device
 * @param key Chave a ser procurada 
 * @return Retorna:
 * 	- String (char*) que contém o valor da info_tuple com chave key. 
 * 	- NULL quando a chave não existe no device
 */
char *get_info_value(struct device *dev, char *key);

/**
 * Imprime a lista de devices, cada um com sua respectiva \n
 * lista de info_tuples e seus device filhos.
 *
 * @param dev Device-cabeça da lista de devices
 * @return Status da operação:
 * 	- EXIT_FAILURE: caso o device passado seja NULL
 * 	- EXIT_SUCCESS: caso contrário
 */
int print_device_list(struct device *dev);

#endif /* TYPES_H */
