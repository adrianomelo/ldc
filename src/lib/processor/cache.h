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


/** @file cache.h
 *  @brief Header file auxiliar do plugin de Processador.
 * 
 * O cache.h  tem por objetivo obter informações de cada cache	\n
 * de um processador.						\n
 * As informações são obtidas do dmidecode		      	\n
 * @see dmidecode.h						\n\n
 */

#ifndef CACHE_H
#define CACHE_H 

/** 
 * Tamanho padrão para um buffer, que armazena\n
 * a handle correspondente a uma cache.\n
 */
#define MAX_HANDLE_SIZE 15

#include <ldc/types.h>

/**
 * Obtém um device de cache com todas as informações.
 * Esta função obtém a iézima cache, contendo todas as informações\n
 * desta cache. \n
 * A função retornará uma Estrutura independente de a iézima cache\n
 * existir, cabendo a quem chama a função verficar se a cache existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache.\n
 * @return uma Estrutura contendo todas as informações da iézima cache.
 */
struct device *get_cache(int i);


/**
 * Obtém o handle da iézima cache.
 * Esta função obtém o handle da iézima cache.\n
 * A informação é retornada como conteudo de um nó. Caso não seja possível\n
 * obter a handle, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo ao handle da iézima cache ou\n
 *             uma mensagem de erro.\n
 */
struct info_tuple *get_cache_handle(int i);


/**
 * Obtém o socket designation da iézima cache.
 * Esta função obtém o socket designation da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter o socket designation, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo ao socket designation da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_socket_designation(int i);


/**
 * Obtém a configuração da iézima cache.
 * Esta função obtém a configuração da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a configuração da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo a configuração da iézima cache ou\n
 *             uma mensagem de erro.\n
 */
struct info_tuple *get_cache_configuration(int i);


/**
 * Obtém o modo operacional da iézima cache.
 * Esta função obtém o modo operacional da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a informação da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo o modo operacional da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_operational_mode(int i);


/**
 * Obtém a location da iézima cache.
 * Esta função obtém a location da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a informação da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo a location da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_location(int i);


/**
 * Obtém o tamanho instalado da iézima cache.
 * Esta função obtém o tamanho instalado da cache da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a informação da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo o tamanho instalado da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_installed_size(int i);


/** 
 * Obtém o tamanho máximo da iézima cache.
 * Esta função obtém o tamanho máximo da cache da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a informação da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo o tamanho máximo da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_maximum_size(int i);
//struct info_tuple *get_cache_supported_sram_types(int i);


/**
 * Obtém o tipo de sram instalado da iézima cache.
 * Esta função obtém o tipo de sram instalado da cache da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a informação da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo o tipo de sram instalado da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_installed_sram_type(int i);


/**
 * Obtém a velocidade da iézima cache.
 * Esta função obtém a velocidade da cache da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a velocidade da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo a velocidade da iézima cache ou \n
 *             uma mensagem de erro.\n
 */
struct info_tuple *get_cache_speed(int i);


/** 
 * Obtém o tipo de coleta de erro da iézima cache.
 * Esta função obtém o tipo de coleta de erro da cache da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a informação da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo o tipo de coleta de erro da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_error_correction_type(int i);


/**
 * Obtém o tipo de sistema da iézima cache.
 * Esta função obtém o tipo sistema da cache da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a informação da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo o tipo de sistema da iézima \n
 *             cache ou uma mensagem de erro.\n
 */
struct info_tuple *get_cache_system_type(int i);


/** 
 * Obtém a associatividade da iézima cache.
 * Esta função obtém a associatividade da cache da iézima cache.\n
 * A informação é retornada como conteudo de um nó. \n
 * Caso não seja possível obter a velocidade da cache, uma \n
 * mensagem de erro é colocada como conteúdo do nó de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de a iézima cache existir ou não, \n
 * cabendo a quem chama a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return uma Estrutura contendo a associatividade da iézima cache ou \n
 *             uma mensagem de erro.\n
 */
struct info_tuple *get_cache_associativity(int i);

/**
 * Obtém a quantidade de caches.
 * Esta função obtém a quantidade de caches. \n
 * A informação é obtida do dmidecode.\n
 * A função retornará zero caso não seja possível obter tal informação. \n
 * 
 * @return um Inteiro correspondente ao número de devices (instalados ou não)\n
 *             ou zero, caso não consiga obter a informação do dmidecode.\n
 */
int get_caches_count();


/**
 * Verifica se uma handle está dentro de uma dada cache.
 * Esta função verifica se uma handle específica é a mesma handle\n
 * de uma cache.\n
 * A informação é obtida do dmidecode.\n
 * A função retornará zero caso não possua, e um, caso possua.\n
 * 
 * @param handle um char *, a handle para se procurar na Estrutura \n
 *             passada no segundo parâmetro.\n
 * @param cache um struct device *, uma estrutura para se procurar \n
 *             pela handle passada como argumento.\n
 * @return um Inteiro sendo 1, caso a cache possua o handle procurado, e 0,\n
 *             caso contrário.\n
 */
int has_cache_handle(char *handle, struct device *cache);


/** 
 * Obtém o handle da iézima cache.
 * Esta função obtém o handle da iézima cache.\n
 * A informação é retornada. Caso não seja possível obter a handle, \n
 * uma mensagem de erro é retornada.\n
 * A informação é obtida do dmidecode. A função retornará uma string\n
 * independente de a iézima cache existir ou não, cabendo a quem chama \n
 * a função verificar se a mesma existe.\n
 * 
 * @param i um Inteiro correspondente á iézima cache inventariada.\n
 * @return um char*, contendo a handle da iézima cache ou uma mensagem \n
 *             de erro.\n
 */
char *get_cache_handle_value(int i);

#endif


