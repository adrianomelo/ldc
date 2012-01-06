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


/** @file processor.h
 *  @brief Header file do plugin de Processador.
 * 
 * O plugin de processador tem por objetivo obter informações	\n
 * sobre os processadores, suas caches cores.			\n
 * presentes no Sistema.			              \n\n
 */


#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <ldc/types.h>

/**
 * Executa o plugin referente ao processador.
 * Função que executa o plugin de processador, detectando\n
 * todos os processadores, obtendo também as caches associadas\n
 * referentes a cada core e os cores, reais ou simulados, de \n
 * cada processador.\n
 * As informações de cada processador são adicionadas á estrutura\n
 * passada como parâmetro.\n
 * 
 * @param[in,out] dev Estrutura raiz do plugin de memória, que será\n
 *                    usada como estrutura de acesso a todas as\n
 *                    informações geradas por esse plugin.\n
 *
 * @return um Inteiro que pode ser:
 * 	       - SUCCESS : quando o plugin executar com sucesso
 * 	       - ERROR   : quando o plugin falhar de alguma maneira 
 */
int get_info(struct device *dev);


/**
 * Insere em device informações sobre o processador. 
 * Esta função detecta todos os processadores e cria estruturas, cada\n
 * uma referente a cada processador e as adiciona como filhos da estrutura\n
 * passada como parametro.\n
 * Caso não seja possível obter a quantidade de processadores real, esta\n
 * função adiciona um processador com as informações que for possível obter.\n
 *
 * @param device Estrutura pai, que terá seus filhos representando cada\n
 *               processador de memória presente.\n
 */
void set_processor_device(struct device *device);


/**
 * Obtém a família do iézimo processador.
 * Esta função obtém a família do iézimo processador e retorna como conteúdo\n
 * de uma estrutura, cabendo a quem chama a função, verificar se o iézimo \n
 * processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja\n
 *               inventariar.\n
 * @return uma estrutura contendo a família do iézimo processador ou uma\n
 *               mensagem de erro.\n
 */
struct info_tuple *get_processor_family(int i);


/**
 * Obtém a versão (modelo) do iézimo processador.\n
 * Esta função obtém a versão (modelo)  do iézimo processador e retorna \n
 * como conteúdo de uma estrutura, cabendo a quem chama a função, verificar\n
 * se o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 *
 * @param i um Inteiro correspondente ao iézimo processador que se deseja\n
 *               inventariar.\n
 * @return uma estrutura contendo a versão do iézimo processador ou uma\n
 *               mensagem de erro.\n
 */
struct info_tuple *get_processor_version(int i);


/** 
 * Obtém o socket designation do iézimo processador.
 * Esta função obtém o socket designation  do iézimo processador e retorna \n
 * como conteúdo de uma estrutura, cabendo a quem chama a função, verificar se\n
 * o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja\n
 &               inventariar.\n
 * @return uma estrutura contendo o socket designation do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
struct info_tuple *get_processor_socket_designation(int i);


/** 
 * Obtém o fabricante (vendor) do iézimo processador.
 * Esta função obtém o fabricante (vendor)  do iézimo processador e retorna \n
 * como conteúdo de uma estrutura, cabendo a quem chama a função, verificar se\n 
 * o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja inventariar.\n
 * @return uma estrutura contendo o fabricante (vendor) do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
struct info_tuple *get_processor_manufacturer(int i);


/**
 * Obtém o ID do iézimo processador.
 * Esta função obtém o ID do iézimo processador e retorna \n
 * como conteúdo de uma estrutura, cabendo a quem chama a função, verificar se \n
 * o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja inventariar.\n
 * @return uma estrutura contendo o ID do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
struct info_tuple *get_processor_id(int i);


/**
 * Obtém a voltagem do iézimo processador.
 * Esta função obtém a voltagem do iézimo processador e retorna \n
 * como conteúdo de uma estrutura, cabendo a quem chama a função, verificar se\n
 * o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja inventariar.\n
 * @return uma estrutura contendo a voltagem do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
struct info_tuple *get_processor_voltage(int i);


/**
 * Obtém a frequência do iézimo processador.
 * Esta função obtém a frequência do iézimo processador e retorna \n
 * como conteúdo de uma estrutura, cabendo a quem chama a função, verificar se\n
 * o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja inventariar.\n
 * @return uma estrutura contendo a frequência do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
struct info_tuple *get_processor_external_clock(int i);


/** 
 * Obtém o Handle da cache L1 do iézimo processador.
 * Esta função obtém o Handle da cache L1 do iézimo processador e retorna \n
 * a informação.\n
 * Cabe a quem chama a função verificar se o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja \n
 *               obter a informação.\n
 * @return uma char *, a Handle da cache L1 do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
char *get_processor_l1_cache_handle(int i);


/**
 * Obtém o Handle da cache L2 do iézimo processador.
 * Esta função obtém o Handle da cache L2 do iézimo processador e retorna \n
 * a informação.\n
 * Cabe a quem chama a função verificar se o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro correspondente ao iézimo processador que se deseja \n
 *               obter a informação.\n
 * @return uma char *, a Handle da cache L2 do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
char *get_processor_l2_cache_handle(int i);


/**
 * Obtém o Handle da cache L3 do iézimo processador.
 * Esta função obtém o Handle da cache L3 do iézimo processador e retorna \n
 * a informação.\n
 * Cabe a quem chama a função verificar se o iézimo processador existe ou não.\n
 * A informação é obtida do dmidecode.\n
 * Caso não seja possível obter tal informação, uma mensagem de erro é\n
 * retornada no conteudo da estrutura de retorno.\n
 * 
 * @param i um Inteiro  correspondente ao iézimo processador que se deseja \n
 *               obter a informação.\n
 * @return uma char *, a Handle da cache L3 do iézimo processador\n
 *               ou uma mensagem de erro.\n
 */
char *get_processor_l3_cache_handle(int i);


/**
 * Obtém a quantidade de processadores.
 * Esta função obtém a quantidade de devices de processadores.\n
 * A informação é obtida do dmidecode. \n
 * A função retornará 1 caso não seja possível obter tal informação\n
 * (partindo do senso de que sempre existe pelo menos 1 processador)\n
 * 
 * @return um Inteiro correspondente ao número de processadores, ou\n
 *               1 (número mínimo de processadores) , caso não se consiga \n
 *               obter a informação.\n
 */
int get_processors_count();

#endif


