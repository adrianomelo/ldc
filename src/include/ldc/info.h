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


/**
 * @file info.h
 * @brief Header file com a função get_info
 *
 * A função get_info é a interface externa de cada um dos plugin do LDC, \n
 * a partir dessa função é que as informações de hardware são coletadas.
 */

#ifndef INFO_H
#define INFO_H

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
 * @param[in,out] device Estrutura raiz do plugin de memória, que será\n
 *                    usada como estrutura de acesso a todas as\n
 *                    informações geradas por esse plugin.\n
 *
 * @return um Inteiro que pode ser:
 * 	       - SUCCESS : quando o plugin executar com sucesso
 * 	       - ERROR   : quando o plugin falhar de alguma maneira 
 */
int get_info (struct device* device);

#endif
