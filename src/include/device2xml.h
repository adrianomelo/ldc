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


/** @file device2xml.h
 *  @brief Header file do gerador de XML.
 * 
 * O gerador de XML recebe as informações obtidas dos plugins	\n
 * e as informações de configuração e, com isso, gera um XML	\n
 * com essas informações.			              \n\n
 */

#ifndef DEVICE2XML_H
#define DEVICE2XML_H

#include <ldc/hashtable.h>
#include <ldc/types.h>


/**
 * Gera um arquivo XML contendo as informações dos plugins.
 * Função que recebe as informações dos plugins e informações\n
 * de configuração como parâmetro e gera um arquivo XML.
 * 
 * @param dev Estrutura contendo as informações de todos\n
 *                    os plugins executados com sucesso.
 * @param config hash_table contendo as configurações do arquivo\n
 *                    de configuração (como nome do XML).\n
 *
 * @return um Inteiro que pode ser:
 * 	       - SUCCESS : quando o XML é gerado com sucesso.
 * 	       - ERROR : quando o device passado como argumento é NULL.
 */

int device2xml (struct device *device, hash_table *config);

/**
 * Gera a string a ser escrita no XML.
 * Função que recebe um device contendo as informações de\n
 * todos os plugins executados com sucesso e escreve o XML\n
 * contendo o cabeçalho do XML e todas estas informações.
 * Esta função chama a função append_xml_device passando o\n
 * mesmo device como parâmetro.\n
 * 
 * @param device Estrutura contendo as informações de todos\n
 *                    os plugins executados com sucesso.\n
 *
 * @return char *, contendo a string final a ser escrita no XML.\n
 */
char *append_xml_meta (struct device *device);


/**
 * Gera a parte da string a ser escrita no XML correspondente aos plugins.
 * Função que recebe um device contendo as informações de\n
 * todos os plugins executados com sucesso, e gera uma string\n
 * contendo todas estas informações no formato a ser escrito\n
 * no XML.\n
 * Esta função chama a função append_xml_info_tuple passando\n
 * a info_tuple principal de cada device como parâmetro.\n
 * 
 * @param device Estrutura contendo as informações de todos\n
 *                    os plugins executados com sucesso.\n
 *
 * @return char *, contendo a string com as informações dos\n
 *                    plugins a ser escrita no XML.\n
 */
char *append_xml_device (struct device *device);


/**
 * Gera a parte da string a ser escrita no XML correspondente a cada informação dos plugins.
 * Função que recebe o info_tuple principal de um device\n
 * contendo uma informação deste plugin, e gera uma string\n
 * referente a esta informação, segundo o formato:\n
 * <info key="KEY" value="VALUE" />\n
 * sendo KEY a key, e VALUE a value contida na info_tuple\n
 * passada como parâmetro.\n
 * O mesmo procedimento é feito para todas as estruturas da\n
 * lista.
 * 
 * @param info Estrutura, head de uma lista, contendo uma informação de um plugin\n
 *
 * @return char *, contendo a string com as informações da lista de info_tuple\n
 *                    passada como parâmetro.\n
 */
char *append_xml_info_tuple (struct info_tuple *info);

#endif
