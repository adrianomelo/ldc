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


/** @file motherboard.h
 *  @brief Header file do plugin de Placa Mãe.
 * 
 * O plugin de placa mãe tem por objetivo obter informações	\n
 * sobre a placa mãe e itens relacionados.			\n\n
 * As informações obtidas são:			        	\n
 *   - System Vendor
 *   - System Product
 *   - System Version
 *   - System Serial Number
 *   - System UUID
 *   - BIOS Vendor
 *   - BIOS Release Date
 *   - Baseboard Vendor
 *   - Baseboard Product
 *   - Baseboard Version
 *   - Baseboard Serial Number
 *   - Chassis Vendor
 *   - Chassis Type
 *   - Chassis Version
 *   - Chassis Serial Number
 */
#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

/**
 * Obtém uma estrutura, struct device *, contendo todas as informações de sistema.
 * Esta função retorna uma estrutura, struct device *, contendo todas as 	\n
 * informações de sistema.							\n
 * Todas as informações são obtidas do dmidecode.				\n
 * As informações contidas na estrutura de retorno são:				\n
 *   - System Vendor
 *   - System Product
 *   - System Version
 *   - System Serial Number
 *   - System UUID\n
 * 
 * @return uma estrutura struct device  *, contendo todas as informações 	\n
 *             de sistema.							\n
 */

struct device *get_system();

/**
 * Obtém uma estrutura, struct device *, contendo todas as informações da BIOS.
 * Esta função retorna uma estrutura, struct device *, contendo todas as 	\n
 * informações da BIOS.								\n
 * Todas as informações são obtidas do dmidecode.				\n
 * As informações contidas na estrutura de retorno são:				\n
 *   - BIOS Vendor
 *   - BIOS Release Date\n
 * 
 * @return uma estrutura struct device  *, contendo todas as informações 	\n
 *             da BIOS.								\n
 */
struct device *get_bios();

/**
 * Obtém uma estrutura, struct device *, contendo todas as informações da baseboard.
 * Esta função retorna uma estrutura, struct device *, contendo todas as 	\n
 * informações da baseboard.							\n
 * Todas as informações são obtidas do dmidecode.				\n
 * As informações contidas na estrutura de retorno são:				\n
 *   - Baseboard Vendor
 *   - Baseboard Product
 *   - Baseboard Version
 *   - Baseboard Serial Number\n
 * 
 * @return uma estrutura struct device  *, contendo todas as informações 	\n
 *             da baseboard.							\n
 */
struct device *get_baseboard();

/**
 * Obtém uma estrutura, struct device *, contendo todas as informações de chassis.
 * Esta função retorna uma estrutura, struct device *, contendo todas as 	\n
 * informações da chassis.							\n
 * Todas as informações são obtidas do dmidecode.				\n
 * As informações contidas na estrutura de retorno são:				\n
 *   - Chassis Vendor
 *   - Chassis Type
 *   - Chassis Version
 *   - Chassis Serial Number\n
 * 
 * @return uma estrutura struct device  *, contendo todas as informações 	\n
 *             da chassis.							\n
 */
struct device *get_chassis();

#endif
