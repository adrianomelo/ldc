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


/** @file config.h
 *  @brief Header file contendo funções para fazer o carregamento das configurações.
 *
 * Este arquivo contém funções para fazer o carregamento das configurações	\n
 * espeficicadas no arquivo de configuração do LDC. 				\n
 *
 * @see Documento Manual do Usuário - LDC (sessão de configuração)		\n
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <ldc/hashtable.h>
#include <prefix.h>

/** 
 * char * contendo o caminho completo para o arquivo de configuração do LDC.	\n
 * Este nome é padrão, passado como parâmetro para todas as funções definidas	\n
 * neste header.								\n
 */
#ifdef PREFIX
#define CONFIG_FILE STR(PREFIX/etc/ldc.conf)
#else
#define CONFIG_FILE "/usr/etc/ldc.conf"
#endif

/**
 * Carrega as informações contidas no arquivo de configuração e as adiciona na hash_table passada como parâmetro.
 * Função que recebe uma hash_table e adiciona a ela as configurações especificadas	\n
 * no arquivo de configuração cujo caminho é passado no segundo parâmetro.		\n
 * Esta função chama a função auxiliar parse_tuple para auxiliar a passar as informações\n
 * do arquivo para a hash_table.							\n
 *
 * @param table hash_table *, Estrutura onde serão adicionadas as configurações do LDC.\n
 * @param config_file char *, caminho para o arquivo de configuração que será lido.	\n
 *
 * @return um Inteiro que pode ser:							\n
 * 	       - SUCCESS : quando o carregamento é executado com sucesso.		
 * 	       - ERROR : quando algum dos parâmetros passados é NULL.
 */
int load_config (hash_table *table, char *config_file);

/**
 * Recebe uma linha do arquivo de configuração e cria uma hash_table* contendo a informação desta linha.
 * Função que recebe uma linha do arquivo de configuração e, caso essa linha tenha uma	\n
 * atribuição, esta atribuição é adicionada a uma hash_table e ela é retornada.		\n
 * Caso a linha não contenha uma atribuição (ex: comentário), a função retorna NULL.	\n
 * Esta função é chamada pela função load_config, que passa cada uma das linhas		\n
 * do arquivo de configuração como parâmetro para esta função.				\n
 *
 * @param string char *, string contendo uma linha do arquivo de configuração.		\n
 *
 * @return hash_info *, Estrutura contendo a informação da string, caso a string seja 	\n
 * 			uma atribuição. Caso contrário, a função retorna NULL.		\n
 */
hash_info *parse_tuple_to_hash (char *string);

#endif

