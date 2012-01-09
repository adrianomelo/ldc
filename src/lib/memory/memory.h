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


/** @file memory.h
 *  @brief Header file do plugin de Memória.
 * 
 * O plugin de memória tem por objetivo obter informações	\n
 * sobre os devices de memória instalados.			\n
 * presentes no Sistema.			              \n\n
 * As informações obtidas são:			        	\n
 *   - Vendor
 *   - Factor
 *   - Type
 *   - Type Detail
 *   - Size
 *   - Serial Number
 *   - Speed
 *   - Maximum Total Size
 *   - Maximum Module Size
 *   - Slots
 *   - Voltage
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <ldc/types.h>


/**
 * Executa o plugin de memória.
 * O plugin de memória detecta o número de devices de memória,\n
 * verifica os que estão instalados e obtém as informações delas.\n
 * Os devices ficam disponíveis através da estrutura passada como\n
 * parâmetro.\n
 * 
 * @param[in,out] dev Estrutura raiz do plugin de memória, que será\n
 *                    usada como estrutura de acesso a todas as\n
 *                    informações geradas por esse plugin.\n
 *
 * @return um Inteiro que pode ser:
 * 	       - SUCCESS : quando o plugin executar com sucesso
 * 	       - ERROR   : quando o plugin falhar de alguma maneira 
 */

int get_info(struct device *device);


/**
 * Insere em memory informações sobre cada pente de memória.
 * Esta função detecta todos os devices de memória e cria nós filhos\n
 * da estrutura passada como parâmetro para representar cada um dos\n
 * devices de memória instalado.\n
 * Caso não haja devices de memória instalados ou não seja possível\n
 * obter informação da quantidade de módulos instalados, é adicionado\n
 * um nó filho contendo apenas informação de erros como 'Informação\n
 * Ausente'.\n
 *
 * @param memory Estrutura pai, que terá seus filhos representando cada\n
 *                device de memória presente.\n
 */
void set_memory(struct device *memory);


/**
 * Obtém o maior tamanho de módulo de memória suportado.
 * Esta função obtém o maior tamanho de módulo de memória suportado\n
 * e cria um nó contendo a informação.\n
 * A informação é obtida do dmidecode.\n
 * 
 * @return uma estrutura contendo qual o maior tamanho que cada modulo de\n
 *            memória pode ter ou uma informação de erro caso não seja \n
 *            possível obter tal informação.\n
 * @see dmidecode\n
 */
struct info_tuple *get_maximum_memory_module_size();


/**
 * Obtém o maior tamanho de memória suportado.
 * Esta função obtém o maior tamanho de memória suportado, correspondendo\n
 * a soma do maximo de memoria possivel de cada device suportado e cria um\n
 * nó contendo esta informação.\n
 * A informação é obtida do dmidecode.\n
 *
 * @return uma estrutura contendo o maior tamanho de memória suportado\n
 *            ou uma informação de erro caso não seja possível obter tal\n
 *            informação.\n
 */
struct info_tuple *get_maximum_memory_total_size();


/**
 * Obtém a voltagem de cada módulo de memória.
 * Esta função obtém a diferença de potencial entre os extremos de cada\n
 * módulo de memória. A informação é obtida do dmidecode.\n
 *
 * @return uma estrutura struct info_tuple *, contendo a voltagem de cada\n
 *            módulo de memória ou uma mensagem de erro.\n
 */
struct info_tuple *get_memory_module_voltage();


/**
 * Obtém o número de slots de memória associados.
 * Esta função obtém a o número de slots de memória, ou seja, quantos devices\n
 * de memória são suportados. A informação é obtida do dmidecode.\n
 * 
 * @return uma estrutura struct info_tuple *, contendo o número de slots de memória.\n
 */
struct info_tuple *get_associated_memory_slots_number();


/**
 * Obtém um device de memória com todas as informações.
 * Esta função obtém o iézimo device de memória, contendo todas as informações\n
 * deste device. Entre elas estão:
 * - Vendor
 * - Factor
 * - Type
 * - Type Detail
 * - Size
 * - Serial
 * - Speed
 * \n
 * A função retornará uma Estrutura independente de o iézimo device\n
 * estar instalado, cabendo a quem chama a função verficar se o device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device que se deseja obter\n
 *             as informações.\n
 * @return uma estrutura struct device *, contendo todas as informações do\n
 *             iézimo device de memória.\n
 */
struct device *get_memory_physical_device(int i);


/**
 * Obtém o fabricante (vendor) do iézimo device de memória.
 * Esta função obtém o fabricante (vendor) do iézimo device de memória.\n
 * A informação é retornada como conteúdo de um nó. Caso não seja possível\n
 * obter o fabricante, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno.\n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de o iézimo device de memória existir ou não, \n
 * cabendo a quem chama a função verificar se o iézimo device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória que será \n
               inventariado.\n
 * @return uma estrutura struct info_tuple *, contendo o fabricante (vendor) do\n
 *             iézimo device de memória ou uma mensagem de erro.\n
 */
struct info_tuple *get_memory_device_manufacturer(int i);


/**
 * Obtém o factor do iézimo device de memória.
 * Esta função obtém o factor do iézimo device de memória.\n
 * A informação é retornada como conteúdo de um nó. Caso não seja possível\n
 * obter o factor, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno.\n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de o iézimo device de memória existir ou não, \n
 * cabendo a quem chama a função verificar se o iézimo device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória que será\n
               inventariado.\n
 * @return uma estrutura struct info_tuple *, contendo o factor do iézimo device de\n
 *             memória ou uma mensagem de erro.\n
 */
struct info_tuple *get_memory_device_factor(int i);


/**
 * Obtém o tipo do iézimo device de memória.
 * Esta função obtém o tipo do iézimo device de memória.\n
 * A informação é retornada como conteúdo de um nó. Caso não seja possível\n
 * obter o tipo, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno.\n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de o iézimo device de memória existir ou não, \n
 * cabendo a quem chama a função verificar se o iézimo device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória que será \n
 *             inventariado.\n
 * @return uma estrutura struct info_tuple *, contendo o tipo do iézimo device de\n
 *             memória ou uma mensagem de erro.
 */
struct info_tuple *get_memory_device_type(int i);


/**
 * Obtém os detalhes a respeito tipo do iézimo device de memória.
 * Esta função obtém detalhes a respeito do tipo do iézimo device de memória.\n
 * A informação é retornada como conteúdo de um nó. Caso não seja possível\n
 * obter algum detalhe sobre o tipo, uma mensagem de erro é colocada como \n
 * conteúdo do nó de retorno.\n 
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de o iézimo device de memória existir ou não, \n
 * cabendo a quem chama a função verificar se o iézimo device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória  que será \n
 *             inventariado.\n
 * @return uma estrutura struct info_tuple *, contendo algum detalhe sobre o tipo do\n
 *             iézimo device de memória ou uma mensagem de erro.\n
 */
struct info_tuple *get_memory_device_type_detail(int i);


/**
 * Obtém o tamanho do iézimo device de memória.
 * Esta função obtém o tamanho do iézimo device de memória.\n
 * A informação é retornada como conteúdo de um nó. Caso não seja possível\n
 * obter o tamanho, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno.\n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de o iézimo device de memória existir ou não,\n
 * cabendo a quem chama a função verificar se o iézimo device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória que será\n
 *             inventariado.\n
 * @return uma estrutura struct info_tuple *, contendo o tamanho do iézimo \n
 *             device de memória ou uma mensagem de erro.\n
 */
struct info_tuple *get_memory_device_size(int i);


/**
 * Obtém o serial do iézimo device de memória.
 * Esta função obtém o serial do iézimo device de memória.\n
 * A informação é retornada como conteúdo de um nó. Caso não seja possível\n
 * obter o serial, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de o iézimo device de memória existir ou não,\n
 * cabendo a quem chama a função verificar se o iézimo device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória que será \n
 *             inventariado.\n
 * @return uma estrutura struct info_tuple *, contendo o serial do iézimo device de\n
 *             memória ou uma mensagem de erro.\n
 */
struct info_tuple *get_memory_device_serial(int i);


/**
 * Obtém a velocidade do iézimo device de memória.
 * Esta função obtém o serial do iézimo device de memória.\n
 * A informação é retornada como conteúdo de um nó. Caso não seja possível\n
 * obter a velocidade, uma mensagem de erro é colocada como conteúdo do nó\n
 * de retorno. \n
 * A informação é obtida do dmidecode. A função retornará uma\n
 * estrutura independente de o iézimo device de memória existir ou não, \n
 * cabendo a quem chama a função verificar se o iézimo device existe.\n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória que será \n
 *             inventariado.
 * @return uma estrutura struct info_tuple *, contendo a velocidade do iézimo device de\n
 *             memória ou uma mensagem de erro.\n
 */
struct info_tuple *get_memory_device_speed(int i);


/**
 * Obtém a quantidade de devices de memória (instalados ou não).
 * Esta função obtém a quantidade de devices de memória, sendo eles instalados\n
 * ou não. \n
 * A informação é obtida do dmidecode. \n
 * A função retornará zero caso não seja possível obter tal informação. \n
 * 
 * @return um Inteiro correspondente ao número de devices (instalados ou não)\n
 *             ou zero, caso não consiga obter a informação do dmidecode.\n
 */
int get_total_memory_physical_devices();


/** 
 * Verifica se o iézimo device de memória está instalado ou não.
 * Esta função verifica se o iézimo device de memória está instalado ou não,\n
 * e retorna um inteiro, sendo ele 1 caso esteja instalado e 0 caso não esteja\n
 * ou caso não tenha sido possível obter tal informação. \n
 * A informação é obtida do dmidecode.\n
 * A função retornará zero caso não seja possível obter tal informação. \n
 * 
 * @param i  Inteiro correspondente ao iézimo device de memória que se\n
 *             deseja saber se está instalado.\n
 * @return um Inteiro, sendo ele 1, caso o iézimo device esteja instalado ou\n
 *             0, caso contrário.\n
 */
int is_memory_device_installed(int i);

#endif 

