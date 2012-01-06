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


/** @file lockfile.h
 *  @brief Header file contendo funções travar e destravar um arquivo antes da escrita.
 *
 * Este arquivo contém funções para travar e destravar um arquivo antes da escrita.	\n
 * No Unix não existe lock mandatório, então a trava funciona como um token, e as 	\n
 * outras aplicações que forem acessar este arquivo devem tentar travar com a mesma 	\n
 * função para evitar erros.								\n
 *
 */

#ifndef LOCKFILE_H
#define LOCKFILE_H

/**
 * Trava o arquivo, impedindo que outras aplicações obtenham o token deste arquivo durante sua escrita.	
 * Função que recebe um file descriptor e faz um lock não mandatório no arquivo,	\n
 * cedendo o token daquele arquivo para a aplicação que chamar a função.		\n
 * Caso outra aplicação tente obter o token, o mesmo não será fornecido, até que	\n
 * a aplicação que está com o token o entregue (destrave o arquivo) ou a aplicação	\n
 * seja encerrada.									\n
 *
 * Esta função não garante acesso exclusivo ao arquivo, outras aplicações que não	\n
 * tentarem obter o token antes de escrever no arquivo poderão escrever no mesmo	\n
 * normalmente.										\n
 *
 * @param fd int, um Inteiro representando o file descriptor de uma arquivo (obtida no	\n
 *             retorno de popen).							\n
 *
 * @return um Inteiro que pode ser:							\n
 * 	       - SUCCESS : quando o lock é feito com sucesso (o token é obtido).		
 * 	       - ERROR : quando o lock não é feito (parâmetro inválido ou token ocupado).
 */

int lock_file (int fd);

/**
 * Destrava o arquivo, permitindo que outras aplicações obtenham o token para escrever no mesmo.
 * Função que recebe um file descriptor e faz um unlock no arquivo, possibilitando que	\n
 * outras aplicações possam obter o token e fazer o lock não mandatório no arquivo.	\n
 *
 * @param fd int, um Inteiro representando o file descriptor de uma arquivo (obtida no	\n
 *             retorno de popen).							\n
 *
 * @return um Inteiro que pode ser:							\n
 * 	       - SUCCESS : quando o unlock é feito com sucesso (o token é desocupado).		
 * 	       - ERROR : quando o lock não é feito (parâmetro inválido ou não é possível destravar).
 */
int unlock_file (int fd);

#endif 

