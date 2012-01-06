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


/** @file dmidecode.h
 *  @brief Header file de funções para obter informações do dmidecode.
 *  @see dmidecode
 *
 * O dmidecode.h tem por objetivo fornecer uma interface segura \n
 * para obtenção de informações do dmidecode. 			\n\n
 * Caso o dmidecode não esteja instalado, as funções retornarão sempre\n
 * alguma mensagem de erro, ou algum número neutro, de forma que não interfira\n
 * no inventário de outras informações, nem de outros plugins.\n
 * O mesmo acontece se a execução do plugin for feita por um usuário sem\n
 * permissão (não super-usuário).\n\n
 * As funções definidas neste arquivo são usadas pelos plugins:	\n
 *   - Processador
 *   - Memória
 *   - Placa-Mãe
 */

#ifndef DMIDECODE_H
#define DMIDECODE_H

/** 
 * dmi_type para se obter informações do processador.\n
 * Mesmo valor do dmidecode.\n
 */
#define PROCESSOR 4
/** 
 * dmi_type para se obter informações de cache.\n
 * Mesmo valor do dmidecode.\n
 */
#define CACHE 7
/** 
 * dmi_type para se obter informações de memória.\n
 * Mesmo valor do dmidecode.\n
 */
#define MEMORY_PHYSICAL_DEVICE 17
/** 
 * dmi_type para se obter informações do controlador\n
 * de memória.\n
 * Mesmo valor do dmidecode.\n
 */
#define MEMORY_CONTROLLER 5i

/** 
 * Valor para se passar nos parâmetros 'line' quando\n
 * só existe uma ocorrência (não iterativo).\n
 * Ver plugin de processador para melhor compreensão.\n
 */
#define FIRST_LINE 1

/** 
 * Tamanho padrão para um buffer, que armazena\n
 * um comando a ser executado no terminal.\n
 * Comando para obter informações do dmidecode.\n
 */
#define MAX_DMI_COMMAND_SIZE 500
/** 
 * Tamanho padrão para um buffer, que armazena\n
 * a saída de um comando a ser executado no terminal.\n
 * Comando obtendo informações do dmidecode.\n
 */
#define MAX_DMI_OUTPUT_SIZE 500
/** 
 * Tamanho padrão para um buffer, que armazena\n
 * a saída de um comando a ser executado no terminal,\n
 * onde esta saída é um número.\n
 * Comando obtendo número do dmidecode.\n
 */
#define MAX_DMI_OUTPUT_COUNT_SIZE 5


/**
 * Obtém informação do dmidecode.
 * Esta função obtém alguma informação do dmidecode, a escolha da informação\n
 * é feita de acordo com os parâmetros passados, que são nada mais do que \n
 * filtros para poder obter apenas a informação desejada.\n
 * A função retornará um char * alocado dinamicamente, com a informação\n
 * selecionada pelos parâmetros ou uma mensagem de erro, caso não seja\n
 * possível obter tal informação.\n
 * Como o retorno é alocado dinamicamente, cabe a quem chama a função,\n
 * liberar memória.\n
 *
 * @param dmi_type um Inteiro, const int, o tipo do dispositivo que se deseja 
 *                obter a informação, no caso do processador, dmi_type = 4, \n
 *                (para mais informações, ver 'man dmidecode').\n
 * @param filter  const char *, filtra as linhas do dmidecode para apenas\n
 *                aquelas que possuem esse filtro.\n
 * @param line    um Inteiro. Após a filtragem, podem existir várias linha de retorno,\n
 *                a linha considerada no retorno será aquela passada em line.\n
 *                É importante saber quantas linhas existem, para isso, deve-\n
 *                se fazer uso da função get_dmidecode_count(char *filter).\n
 * @param begin   um Inteiro. Uma vez selecionada a linha pelo argumento passado em\n
 *                line, é necessário saber a partir de qual string deseja-se\n
 *                retornar (i.e. se begin for 3, a saída será a partir da 3ª\n
 *                string da linha passada em line.\n
 * @return char *, alocado dinamicamente contendo a informação de acordo com\n
 *                os parâmetros passados ou uma mensagem de erro (informando\n
 *                que a dependência não existe ou que não foi possível obter a\n
 *                informação).\n
 */
char *get_dmidecode_output(const int dmi_type, const char *filter, const int line, const int begin);


/**
 * Obtém informação do dmidecode baseado numa keyword.
 * Esta função obtém alguma informação do dmidecode, a escolha da informação\n
 * é feita de acordo com os parâmetros passados, que são nada mais do que \n
 * filtros para poder obter apenas a informação desejada.\n
 * A função retornará um char * alocado dinamicamente, com a informação\n
 * selecionada pelos parâmetros ou uma mensagem de erro, caso não seja\n
 * possível obter tal informação.\n
 * Como o retorno é alocado dinamicamente, cabe a quem chama a função,\n
 * liberar memória.\n
 *
 * @param keyword const char *, o keyword referente a informação que se deseja\n
 *                obter (ver man dmidecode).\n
 * @param line um Inteiro, int. pós a filtragem, podem existir várias linha de retorno,\n
 *                a linha considerada no retorno será aquela passada em line.\n
 *                É importante saber quantas linhas existem, para isso, deve-\n
 *                se fazer uso da função get_dmidecode_count(char *filter).\n
 * @return char *, alocado dinamicamente contendo a informação de acordo com\n
 *                os parâmetros passados ou uma mensagem de erro (dependência não\n
 *                instalada ou dizendo que não foi possível obter a informação).\n
 */
char *get_dmidecode_keyword_output(const char *keyword, const int line);


/**
 * Obtém a quantidade de linhas contendo determinado filtro no dmidecode.
 * Esta função obtém a quantidade de linhas contendo o filtro na saída do\n
 * 'dmidecode -t dmi_type'.\n
 *
 * @param dmi_type um Inteiro, const int, o tipo do dispositivo que se deseja 
 *                obter a informação, no caso do processador, dmi_type = 4, \n
 *                (para mais informações, ver 'man dmidecode').\n
 * @param filter const char *, filtro que as linhas devem conter para estar\n
 *                dentro da contagem.\n
 * @return um Inteiro, a quantidade de linhas que possuem o filtro passado no\n
 *                parâmetro na saída do 'dmidecode -t dmi_type'.
 *                Se não for possível obter a informação (ex: dependência inexistente\n
 *		  ou não houver permissão), a função retornará 0 (zero).
 */
int get_dmidecode_count(int dmi_type, const char *filter);


/**
 * Verifica se uma keyword é válida.
 * Esta função recebe uma keyword como argumento e verifica se ela é uma\n
 * keyword válida. Esta keyword nunca será modificada, podendo-se passar\n
 * uma string literal ou alocada dinamicamente, caso alocada dinamicamente,\n
 * cabe a quem chamou a função desalocar a mesma.\n
 * Para mais detalhes ver 'man dmidecode' ou 'dmidecode --string'.\n
 *
 * @param keyword const char *, keyword para ser verificada.\n
 * @return um Inteiro, retorna 1 caso a keyword seja válida, e 0 caso contrário.\n
 */
int is_valid_keyword(const char *keyword);

#endif
