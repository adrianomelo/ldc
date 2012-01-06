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
 * @file libraries.h
 * @brief Header file para as funções de carregamento dos plugins
 *
 * O LDC irá varrer a pasta que contém as bibliotecas (padrão: /lib/) e \n
 * procurar pelos arquivos que começam com 'libldc' e terminam com '.so'.\n
 * 
 * Com cada biblioteca dessas o LDC irá tentar mapear a função get_info, \n
 * quando o mapeamento desse símbolo ocorrer com sucesso o LDC irá executar \n
 * essa função e passar como parâmetro um struct device* que tem como nome \n
 * o nome do arquivo que está sendo aberto (ver função get_plugin_name) \n
 * se as informações forem adicionadas com successo no struct device* passado \n
 * como parâmetro (retornar SUCCESS), essas informações serão incorporadas ao \n
 * resto das informações inventariadas pelo LDC. \n
 */

#ifndef LIBRARIES_H
#define LIBRARIES_H

/**
 * char* que aponta para onde as bibliotecas do LDC estão.
 */
#ifdef PREFIX
#define PLUGINS_DIR STR(PREFIX/lib/)
#else
#define PLUGIN_DIR "/usr/lib/"
#endif

#include <ldc/hashtable.h>

/**
 * @var informations é o struct device* que contém todas as informações inventariadas
 */
struct device *informations;

/**
 * função para abrir uma biblioteca do LDC e pegar as informações.
 *
 * A função abre a biblioteca dinâmica apontada pela variável file \n
 * e executa a função get_info. \n\n
 *
 * Caso o file não seja uma biblioteca, haverá uma notificação no arquivo de log \n
 * /tmp/ldc.log com a mensagem de erro. \n\n
 *
 * Caso não exista a função "int get_info(struct device*) na biblioteca carregada \n
 * também haverá uma entrada no arquivo de LOG sinalizando esse erro. \n\n
 *
 * Caso tudo seja executado com sucesso, haverá uma entrada no LOG sinalizando que as \n
 * informações do plugin foram obtidas com sucesso.
 *
 * @param device é um device vazio para as informações serem inclusas nele
 * @param file é o caminho absoluto para o plugin
 * @param config é uma hash_table contendo as informações do ldc.conf
 * @return se o plugin foi aberto e executado com sucesso
 */
int   open_plugin(struct device *device, char *file, hash_table *config);

/**
 * A partir de um nome como '/lib/libldcnetwork.so', pegar o nome 'network'
 * 
 * A função procura pelo último caracter '/' e o primeiro ponto, ao achar esses dois, \n
 * é verificado se essa string começa com '/libldc'. O nome entre '/libldc' e o ponto \n
 * é retornado como o nome do plugin
 *
 * @param file o caminho absoluto para o plugin
 * @return o nome do plugin
 */
char* get_plugin_name (char *file);

/**
 * Dado um diretório, listar todos os '.so' que estão nele
 *
 * A função opendir() será usada para abrir a pasta a procura dos arquivos dela, \n
 * os arquivos que terminarem com '.so' serão postos em uma lista para o LDC tentar \n
 * abrir com a função open_plugin e o inventário com a biblioteca. \n
 *
 * @param folder caminho absoluto para a pasta com os plugins
 * @param file lista que conterá os '.so' contidos na pasta
 * @return se foi possível abrir a pasta e colocar os '.so' em uma lista
 */
int   list_plugins    (char folder[], struct file_list **file);

#endif

