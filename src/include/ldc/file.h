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


/** @file file.h
 *  @brief Header file contendo função para escrever em arquivo.
 *
 * Este arquivo contém a função principal para se escrever em um arquivo.	\n
 * A função em questão é a write_output. Esta função é usada para se escrever	\n
 * o arquivo XML.								\n
 */

#ifndef FILE_H
#define FILE_H

/**
 * Escreve uma string em um arquivo, podendo adicionar no final do arquivo ou sobrescrever, dependendo do modo.
 * Função que recebe uma string e adiciona e escreve essa string em um arquivo, cujo 	\n
 * nome é passado como parâmetro, podendo adicionar a string no final do arquivo ou 	\n
 * sobrescrever o arquivo, dependendo do modo de escrita, também passado como parâmetro.\n
 * Se algum dos parâmetros for NULL, a função retorna ERROR, e caso o modo de escrita	\n
 * seja diferente de 'w' ou 'a', a função retorna ERROR, exceto se for passada um mode	\n
 * de tamanho maior que, onde é definido 'a' como padrão.				\n\n
 * A função retorna um inteiro, representando o status da operação.			\n
 * 
 * @param string char *, string a ser escrita no arquivo.				\n
 * @param file char *, caminho para o arquivo que será escrito.				\n
 * @param mode char *, o modo de escrita, podendo ser:					\n
 *		- "a" : Adiciona 'string' ao final do arquivo especificado em 'file'.
 *		- "w" : Escreve 'string' no arquivo especificado em 'file'.\n
 *
 * @return um Inteiro que pode ser:							\n
 * 	       - SUCCESS : quando a escrita é executada com sucesso.		
 * 	       - ERROR : quando não consegue escrever ou algum dos argumentos é NULL.
 */
int write_output (char *string, char *file, char *mode);

#endif

