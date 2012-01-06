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


/** @file terminal.h
 *  @brief Header file do Core, que guarda as funções base\n
 *  	   para o uso do terminal (shell) do sistema.
 * 
 * Esse módulo do Core possui funções que devem ser usadas\n
 * como interface para o terminal (shell) do sistema, ou seja,\n
 * quando for necessário executar um comando no terminal.\n\n
 * As funções nesse módulo são:\n
 *   - get_cmd_output()
 *   - open_cmd_stream()
 *   - close_cmd_stream()
 */

#ifndef TERMINAL
#define TERMINAL

#include <stdio.h>


/** 
 * Executa o comando passado como parâmetro,\n
 * e retorna a saída, que deve ter tamanho máximo\n
 * igual à buf_size.
 *
 * Essa função só retorna a primeira linha da saída\n
 * do comando (até o primeiro newline). O comando passado\n
 * irá ser interpretado pelo shell do sistema, podendo-se\n
 * portanto usar caracteres especiais no comando,que serão\n
 * interpretados pelo shell. O buf_size indica o tamanho máximo\n
 * esperado para a saída do comando (incluindo todas as linhas,\n
 * da saída). Essa função faz algumas alterações na string\n
 * retornada pelo comando, como a remoção de newlines e espaços\n
 * em branco da primeira linha da saída. Além disso, não se deve\n
 * esperar que o tamanho do buffer retornado seja igual ao tamanho\n
 * passado como parâmetro, não sendo indicado a modificação in-place,\n
 * desse buffer.\n
 * A string retornada é alocada dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param command String que representa um comando a ser executado\n
 * 		  no shell do sistema.
 *
 * @param buf_size Tamanho do buffer que será usado para armazenar\n
 * 		   a saída completa do comando executado no terminal.\n
 *
 * @return um char *, que pode ser:
 * 	       - saída esperada : quando o comando chamado execute sem
 * 	       			  problemas no terminal, ou seja, o
 * 	       			  comando existe, e a saída do terminal
 * 	       			  não é\n uma string vazia.
 * 	       - UNDEFINED_INFO : quando a saída do terminal for uma\n
 * 	       			  string vazia ou se o comando passado
 * 	       			  não foi encontrado.\n
 * 	       - NULL : quando ocorreu algum problema na execução do\n
 * 	       		do comando, ou algo relacionado à alocação de
 * 	       		memória.\n
 */
char *get_cmd_output(const char *command, size_t buf_size);

/**
 * Executa o comando passado como parâmetro, e retorna uma\n
 * stream que aponta para sua saída.
 *
 * Essa função é a alternativa à <tt>get_cmd_output()</tt>, quando se\n
 * quer obter/analisar mais do que apenas a primeira linha\n
 * da saída do comando. Porém seu uso, obriga o caller a fazer\n
 * a checagem de erros realizadas internamente no get_cmd_output().\n
 * Ao usar esta função, deve-se fechar a stream através da função\n
 * <tt>close_cmd_stream()</tt>
 *
 * @param command String que representa um comando a ser executado\n
 * 		  no shell do sistema.
 *
 * @return um FILE *, que pode ser:
 * 		- um pipe para a saída do comando : quando der tudo certo.
 * 		- NULL : quando houver algum problema na criação do pipe.
 */
FILE *open_cmd_stream(const char *command);

/**
 * Libera a stream passada como parâmetro e retorna\n
 * um inteiro que indica o status do comando que gerou,\n
 * essa stream.\n
 *
 * Essa função é usada para liberar a stream gerada pela função\n
 * <tt>open_cmd_stream()</tt>. Deve-se notar que na verdade, o\n
 * parâmetro recebido é um endereço de um ponteiro para uma stream,\n
 * pois o pointeiro passado será setado para NULL.\n
 *
 * @param stream Endereço de um pointeiro para uma stream gerada por\n
 * 		 <tt>open_cmd_stream</tt>.
 *
 * @return um <tt>int</tt>, que está definido em errors.h e pode ser:
 * 		- um pipe para a saída do comando : quando der tudo certo.
 * 		- NULL : quando houver algum problema na criação do pipe.
 */
int close_cmd_stream(FILE **stream);


#endif /* TERMINAL */
