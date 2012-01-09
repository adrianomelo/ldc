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


/** @file cpuinfo.h
 *  @brief Header file auxiliar do plugin de Processador.
 * 
 * O cpuinfo.h tem por objetivo obter informações do arquivo		\n
 * /proc/cpuinfo. Este arquivo possui informações sobre os		\n
 * cores de cada processador presente.		          		\n
 * As funções do cpuinfo.h são usadas principalmente pelo cpu_core.h.	\n\n
 */


#ifndef CPUINFO_H
#define CPUINFO_H

/** 
 * Tamanho padrão para um buffer, que armazena\n
 * a saída de um comando a ser executado no terminal.\n
 * Comando obtendo informações do /proc/cpuinfo.\n
 */
#define MAX_CPU_INFO_OUTPUT 500
/** 
 * Tamanho padrão para um buffer, que armazena\n
 * um comando a ser executado no terminal.\n
 * Comando para obter informações do /proc/cpuinfo.\n
 */
#define MAX_CPU_INFO_COMMAND 300

/** 
 * Tamanho padrão para um buffer, que armazena\n
 * a saída de um comando a ser executado no terminal,\n
 * onde esta saída é um número.\n
 * Comando obtendo número do /proc/cpuinfo.\n
 */
#define MAX_CPU_INFO_OUTPUT_COUNT 5

/**
 * Obtém alguma informação do arquivo /proc/cpuinfo.
 * Esta função obtém alguma informação do arquivo /proc/cpuinfo, isso\n
 * de acordo com os parâmetros passados, que são nada mais do que filtros\n
 * para poder obter apenas a informação desejada.\n
 * A função retornará um char * alocado dinamicamente, com a informação\n
 * selecionada pelos parâmetros ou uma mensagem de erro, caso não seja\n
 * possível obter tal informação.\n
 * Como o retorno é alocado dinamicamente, cabe a quem chama a função,\n
 * liberar memória.\n
 *
 * @param filter  const char *, filtra as linhas do cpuinfo para apenas\n
 *                aquelas que possuem esse filtro.\n
 * @param line    um Inteiro após a filtragem, podem existir várias linha \n
 *                de retorno, a linha considerada no retorno será aquela 
 *                passada em line.\n
 *                É importante saber quantas linhas existem, para isso, deve-\n
 *                se fazer uso da função get_cpu_info_output_count.\n
 * @param begin   um Inteiro uma vez selecionada a linha pelo argumento passado\n
 *                em line, é necessário saber a partir de qual string deseja-se\n
 *                retornar (i.e. se begin for 3, a saída será a partir da 3ª\n
 *                string da linha passada em line.\n
 * @return char *, alocado dinamicamente contendo a informação de acordo com\n
 *                os parâmetros passados.\n
 */
char *get_cpu_info_output(const char *filter, int line, int begin);


/**
 * Obtém a quantidade de linhas contendo determinado filtro no\n
 *                arquivo /proc/cpuinfo.
 * Esta função obtém a quantidade de linhas contendo o filtro no arquivo\n
 * /proc/cpuinfo.\n
 *
 * @param filter const char *, filtro que as linhas devem conter para estar\n
 *                dentro da contagem.\n
 * @return um Inteiro, a quantidade de linhas que possuem aquele filtro.\n
 */
int get_cpu_info_output_count(const char *filter);


/**
 * Obtém alguma informação do arquivo /proc/cpuinfo.
 * Esta função obtém alguma informação do arquivo /proc/cpuinfo, isso\n
 * de acordo com os parâmetros passados, que são nada mais do que filtros\n
 * para poder obter apenas a informação desejada.\n
 * A função retornará um char * alocado dinamicamente, com a informação\n
 * selecionada pelos parâmetros ou uma mensagem de erro, caso não seja\n
 * possível obter tal informação.\n
 * Como o retorno é alocado dinamicamente, cabe a quem chama a função,\n
 * liberar memória.\n
 *
 * @param filter const char *, filtra as linhas do cpuinfo para apenas\n
 *                aquelas que possuem esse filtro. Nesta função, porém,\n
 *                são selecionadas apenas linhas sem repetição, no caso,\n
 *                se 3 linhas contiverem este filtro, sendo duas destas\n
 *                iguais, apenas 2 linhas diferentes serão consideradas.\n
 * @param line um Inteiro após a filtragem, podem existir várias linha de retorno,\n
 *                a linha considerada no retorno será aquela passada em line.\n
 *                É importante saber quantas linhas existem, para isso, deve-\n
 *                se fazer uso da função get_cpu_info_output_count_uniq.\n
 * @param begin um Inteiro uma vez selecionada a linha pelo argumento passado em\n
 *                line, é necessário saber a partir de qual string deseja-se\n
 *                retornar (i.e. se begin for 3, a saída será a partir da 3ª\n
 *                string da linha passada em line.\n
 * @return char *, alocado dinamicamente contendo a informação de acordo com\n
 *                os parâmetros passados.\n
 */
char *get_cpu_info_output_uniq(const char *filter, int line, int begin);


/**
 * Obtém a quantidade de linhas diferentes contendo determinado \n
 *                filtro no arquivo /proc/cpuinfo.\n
 *
 * Esta função obtém a quantidade de linhas diferentes contendo o filtro \n
 * no arquivo /proc/cpuinfo. Para se passar um filtro contendo mais de uma\n
 * palavra, deve-se usar aspas simples (i.e. 'filtro com espacos')\n
 * 
 * @param filter const char *, filtro que as linhas devem conter para estar\n
 *                dentro da contagem.\n
 * @return um Inteiro, a quantidade de linhas diferentes que possuem aquele filtro.\n
 */
int get_cpu_info_output_uniq_count(const char *filter);

#endif

