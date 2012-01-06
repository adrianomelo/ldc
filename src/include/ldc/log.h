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
 * @file log.h
 * @brief Header file com as funções de LOG do LDC
 *
 * O log do LDC é um arquivo localizado em /tmp/ldc.log
 */
#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

/**
 * Constante que define o tamanho máximo de uma	\n
 * mensagem de log.				\n
 */
#define MAX_LOG_SIZE 1000

/**
 * Avisa que ocorreu algum erro
 * O aviso de erro será gravado no arquivo /tmp/ldc.log
 * @param message mensagem de erro
 */
void log_warning (char *message, ...);

/**
 * Função a ser chamada quando ocorre um erro grave!
 * O erro será gravado no arquivo /tmp/ldc.log
 * @param message mensagem de erro
 */
void log_error (char *message, ...);

/**
 * Função para fazer o log de alguma mensagem de debug
 * A mensagem será gravada no arquivo /tmp/ldc.log
 * @param message mensagem a ser gravada no log
 */
void log_debug (char *message, ...);

/**
 * Escreve arquivo de log de erros baseado no retorno das funções principais.
 * Função que recebe um código de erro e escreve no log uma mensagem de erro	\n
 * correspondente a esse código.						\n
 *
 * @param code um Inteiro correspondente ao código de erro.			\n
 */
void log_known_error (int code);

#endif

