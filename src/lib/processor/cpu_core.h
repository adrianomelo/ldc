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


/** @file cpu_core.h
 *  @brief Header file auxiliar do plugin de Processador.
 * 
 * O cpu_core.h tem o objetivo de obter as informações sobre os	\n
 * cores do processador.					\n
 * As informações são obtidas pelas funcoes do cpuinfo.h       	\n
 * @see cpuinfo.h						\n\n
 */


#ifndef CPU_CORE_H
#define CPU_CORE_H

#include <ldc/types.h>

/**
 * Obtém um device de core com todas as informações.
 * Esta função obtém o iézimo core (real ou simulado), contendo todas\n
 * as informações deste core.\n
 * A função retornará uma Estrutura independente de o iézimo core\n
 * existir, cabendo a quem chama a função verficar se o iézimo core\n
 * existe (ver int get_cores_count()).\n
 * 
 * @param i um Inteiro correspondente ao iézimo core.\n
 * @return struct device *, uma Estrutura contendo todas as informações\n
 *             do iézimo core.\n
 */
struct device *get_core(int i);


/**
 * Obtém o vendor_id do iézimo core.
 * Esta função obtém o vendor_id do iézimo core.\n
 * A informação é retornada como conteudo de um nó. Caso não seja possível\n
 * obter esta informação, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do /proc/cpuinfo. \n
 * A função retornará uma estrutura independente de o iézimo core existir \n
 * ou não, cabendo a quem chama a função verificar se o iézimo core existe\n
 * (ver int get_cores_count()).\n
 * 
 * @param i um Inteiro correspondente ao iézimo core inventariado.\n
 * @return struct info_tuple *, uma Estrutura contendo o vendor_id do iézimo\n
 *             core ou uma mensagem de erro.\n
 */
struct info_tuple *get_core_vendor_id(int i);


/**
 * Obtém a frequência do iézimo core.\n
 * Esta função obtém a frequência do iézimo core.\n
 * A informação é retornada como conteudo de um nó. Caso não seja possível\n
 * obter esta informação, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do /proc/cpuinfo. \n
 * A função retornará uma estrutura independente de o iézimo core existir \n
 * ou não, cabendo a quem chama a função verificar se o iézimo core existe\n
 * (ver int get_cores_count()).\n
 * 
 * @param i um Inteiro correspondente ao iézimo core inventariado.\n
 * @return struct info_tuple *, uma Estrutura contendo a frequência do iézimo\n
 *             core ou uma mensagem de erro.\n
 */
struct info_tuple *get_core_cpu_mhz(int i);


/**
 * Obtém o physical_id do iézimo core.\n
 * Esta função obtém o physical_id do iézimo core.\n
 * A informação é retornada como conteudo de um nó. Caso não seja possível\n
 * obter esta informação, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do /proc/cpuinfo. \n
 * A função retornará uma estrutura independente de o iézimo core existir \n
 * ou não, cabendo a quem chama a função verificar se o iézimo core existe\n
 * (ver int get_cores_count()).\n
 * 
 * @param i um Inteiro correspondente ao iézimo core inventariado.\n
 * @return struct info_tuple *, uma Estrutura contendo o physical_id do iézimo\n
 *             core ou uma mensagem de erro.\n
 */	
struct info_tuple *get_core_physical_id(int i);


/**
 * Obtém o ID do iézimo core.
 * Esta função obtém o ID do iézimo core.\n
 * A informação é retornada como conteudo de um nó. Caso não seja possível\n
 * obter esta informação, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do /proc/cpuinfo. \n
 * A função retornará uma estrutura independente de o iézimo core existir \n
 * ou não, cabendo a quem chama a função verificar se o iézimo core existe\n
 * (ver int get_cores_count()).\n
 * 
 * @param i um Inteiro correspondente ao iézimo core inventariado.\n
 * @return struct info_tuple *, uma Estrutura contendo o ID do iézimo\n
 *             core ou uma mensagem de erro.\n
 */
struct info_tuple *get_core_id(int i);


/**
 * Obtém a quantidade de cores reais (não simulados) de acordo com o iézimo core.
 *
 * Esta função obtém q quantidade de cores reais de acordo com o iézimo core.\n
 * A informação é retornada como conteudo de um nó. Caso não seja possível\n
 * obter esta informação, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do /proc/cpuinfo. \n
 * A função retornará uma estrutura independente de o iézimo core existir \n
 * ou não, cabendo a quem chama a função verificar se o iézimo core existe\n
 * (ver int get_cores_count()).\n
 * 
 * @param i um Inteiro correspondente ao iézimo core inventariado.\n
 * @return struct info_tuple *, uma Estrutura contendo q quantidade de cores\n
 *             reais (não simulados) de acordo com o iézimo core ou uma men-\n
 *             sagem de erro, caso não seja possível obter tal informação.\n
 */
struct info_tuple *get_cpu_cores_count(int i);


/**
 * Obtém as flags do iézimo core.
 * Esta função obtém as flags do iézimo core.\n
 * A informação é retornada como conteudo de um nó. Caso não seja possível\n
 * obter esta informação, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do /proc/cpuinfo. \n
 * A função retornará uma estrutura independente de o iézimo core existir \n
 * ou não, cabendo a quem chama a função verificar se o iézimo core existe\n
 * (ver int get_cores_count()).\n
 * 
 * @param i um Inteiro correspondente ao iézimo core inventariado.\n
 * @return struct info_tuple *, uma Estrutura contendo as flags do iézimo\n
 *             core ou uma mensagem de erro, caso não seja possível obter\n
 *             tal informação.\n
 */
struct info_tuple *get_core_features(int i);


/**
 * Obtém o iézimo physical_id (physical_id do iézimo core).
 * Esta função obtém o iézimo physical_id, de acordo com cpuinfo.\n
 * A informação é obtida do /proc/cpuinfo.\n
 * A função retornará uma mensagem de erro, caso não seja possível obter\n
 * tal informação. \n
 * A string de retorno é alocada dinamicamente, cabendo a quem chama a\n
 * função liberar memória após seu uso.\n
 * 
 * @param i um Inteiro correspondente ao iézimo physical_id que\n
 *             se deseja obter.\n
 * @return char *, uma string contendo o iézimo physical_id ou uma mensagem\n
 *             de erro, caso não seja possível obter tal informação.\n
 */

char *get_core_physical_id_value(int i);


/**
 * Obtém a quantidade de cores.
 * Esta função obtém a quantidade de cores. \n
 * A informação é obtida do /proc/cpuinfo.\n
 * A função retornará zero caso não seja possível obter tal informação. \n
 * 
 * @return um Inteiro correspondente ao número de cores presentes no \n
 *             /proc/cpuinfo, retornará zero caso não consiga obter\n
 *             tal informação.\n
 */
int get_cores_count();


/**
 * Verifica se uma physical_id está dentro de um core.
 * Esta função verifica se um physical_id específico é o mesmo\n
 * physical_id de um core.\n
 * A função retornará zero (0), caso o core não possua nenhum physical_id\n
 * ou não possua um physical_id igual ao argumento physical_id, e retorna-\n
 * rá um (1), caso possua.\n
 * 
 * @param physical_id char *, um physical_id para se procurar na Estrutura\n
 *             passada no segundo parâmetro.\n
 *             no segundo parâmetro.\n
 * @param core struct device *, uma estrutura para se procurar pelo physical\n
 *             _id dado (primeiro argumento).\n
 * @return um Inteiro, sendo 1, caso o core possua o handle procurado,\n
 *             e 0, caso contrário.\n
 */
int has_physical_id(char *physical_id, struct device *core);


/**
 * Obtém a quantidade de physical_ids únicos (processadores).
 * Esta função obtém a quantidade de processadores de acordo com cpuinfo.\n
 * No caso, ela obtem a quantidade de physical_ids diferentes no arquivo. \n
 * A informação é obtida do /proc/cpuinfo.\n
 * A função retornará zero caso não seja possível obter tal informação. \n
 * 
 * @return um Inteiro correspondente ao número de physical_ids presentes\n
 *             no /proc/cpuinfo, retornará zero caso não consiga obter\n
 *             tal informação.\n
 */
int get_physical_id_uniq_count();


/**
 * Obtém o iézimo physical_id único.
 * Esta função obtém o iézimo physical_id único, de acordo com cpuinfo.\n
 * A informação é obtida do /proc/cpuinfo.\n
 * A função retornará uma mensagem de erro, caso não seja possível obter\n
 * tal informação. \n
 * A string de retorno é alocada dinamicamente, cabendo a quem chama a\n
 * função liberar memória após seu uso.\n
 * 
 * @param i um Inteiro correspondente ao iézimo physical_id único que\n
 *             se deseja obter.\n
 * @return char *, uma string contendo o iézimo physical_id único ou uma\n
 *             mensagem de erro, caso não seja possível obter tal informação.\n
 */
char *get_physical_id_uniq(int i);


#endif

