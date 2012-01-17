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


/** @file network.h
 *  @brief Header file do plugin de Rede.
 * 
 * O plugin de rede tem por objetivo obter informações		\n
 * sobre as interfaces de rede Ethernet e Wireless		\n
 * presentes no Sistema.			              \n\n
 * As informações de interesse são:			        \n
 *   - Fabricante
 *   - Modelo
 *   - Endereço IP
 *   - Endereço MAC
 *   - Gateway
 *   - Servidores DNS
 *   - Link UP
 *   - Link Detected
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__


/** 
 * Tamanho padrão para um buffer, que armazena\n
 * um comando a ser executado no terminal.\n
 */
#define CMD_SIZE 100
/**
 * Tamanho padrão para um buffer, que armazena\n
 * a saída de um comando a ser executado no terminal.\n
 */
#define BUF_SIZE 100
/**
 * Número máximo de DNS's detectados pelo plugin de rede.\n
 */
#define MAX_DNS_NUM 5


/**
 * Executa o plugin de rede.
 * O plugin de rede detecta as interfaces de rede\n
 * presentes no sistema, obtêm as informações de cada\n
 * uma dessas interfaces e as torna disponíveis através\n
 * da estrutura passada como parâmetro.\n
 * 
 * @param[in,out] dev Estrutura raiz do plugin de rede, que será\n
 *                    usada como estrutura de acesso a todas as\n
 *                    informações geradas por esse plugin.\n
 *
 * @return um Inteiro que pode ser:
 * 	       - SUCCESS : quando o plugin executar com sucesso
 * 	       - ERROR   : quando o plugin falhar de alguma maneira 
 */
int   get_info(struct device *dev);

/** 
 * Detecta as interfaces de rede do sistema.
 * Essa função só detecta interfaces do tipo Ethernet\n
 * (e.g. eth0) e  Wireless (e.g. wlan0). Para cada interface\n
 * detectada, a função cria um <tt>device</tt> que terá sua\n
 * variável <tt>device::name</tt> representando o tipo de interface\n
 * (i.e. ethernet ou wireless) e terá sua variável <tt>device::info</tt>\n
 * apontando para uma info_tuple com o nome da interface de rede\n
 * (e.g. eth0). Cada uma dessas estruturas representa uma das\n
 * interfaces detectadas, e todas elas são transformadas em filhas\n
 * da estrutura passada como parâmetro.\n
 *
 * @param network Estrutura pai ou raiz do plugin de rede, que\n
 *                terá seus filhos representando cada interface\n
 *                de rede do sistema.\n
 *
 * @return um Inteiro que pode ser:
 * 	       - SUCCESS : quando a detecção das interfaces ocorrer
 * 	                   sem problema.
 * 	       - ERROR   : quando houver algum erro na detecção.
 */
int   get_interfaces(struct device *network);

/**
 * Insere as informações obtidas da interface de rede\n
 * na estrutura passada como parâmetro.
 * Essa função utiliza o nome da Interface da estrutura passada\n
 * e com essa informação obtêm informações sobre essa interface,\n
 * criando uma into_tuple para cada informação e a inserindo-a na\n
 * estrutura passada como parâmetro.\n
 *
 * @param nic Estrutura que representa uma das interfaces\n
 *            de rede do sistema.\n
 *
 * @return um Inteiro que pode ser:
 * 	       - SUCCESS : quando não houver problemas na inserção
 * 	                   de informações.
 * 	       - ERROR   : quando houver algum problema na inserção.
 */
int   add_nic_info(struct device *nic);

/** 
 * Obtêm o nome do fabricante da interface de\n
 * rede, e o retorna.
 * Este nome é alocado dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param nic Estrutura que representa uma das interface\n
 *            de rede do sistema.\n
 *
 * @return um char *, que pode ser:
 * 	       - fabricante : quando der tudo certo na obtenção do
 * 	                      fabricante. 
 * 	       - UNDEFINED_INFO : quando não for possível obter o
 * 	                          fabricante,\n
 * 	                          provavelmente devido falta de alguma
 * 	                          dependência do LDC.
 * 	       - NULL : quando houver algum problema mais sério, como\n
 * 	                erro ao tentar alocar memória.
 */
char *get_vendor(struct device *nic);

/** 
 * Obtêm o nome do modelo da interface de\n
 * rede, e o retorna.
 * Este nome é alocado dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param nic Estrutura que representa uma das interface\n
 *            de rede do sistema.\n
 *
 * @return um char *, que pode ser:
 * 	       - modelo : quando der tudo certo na obtenção do modelo. 
 * 	       - UNDEFINED_INFO : quando não for possível obter o
 * 	                          modelo,\n
 * 	                          provavelmente devido falta de alguma
 * 	                          dependência do LDC.
 * 	       - NULL : quando houver algum problema mais sério, como\n
 * 	                erro ao tentar alocar memória.
 */
char *get_model(struct device *nic);

/** 
 * Obtêm o endereço IP da interface de\n
 * rede, e o retorna.
 * Este nome é alocado dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param nic Estrutura que representa uma das interface\n
 *            de rede do sistema.\n
 *
 * @return um char *, que pode ser:
 * 	       - endereço IP : quando der tudo certo na obtenção do IP. 
 * 	       - UNDEFINED_INFO : quando não for possível obter o
 * 	                          IP,\n
 * 	                          provavelmente porque o computador não
 * 	                          está conectado\n
 * 	                          com essa interface, e portanto não
 * 	                          possui IP.
 * 	       - NULL : quando houver algum problema mais sério, como\n
 * 	                erro ao tentar alocar memória.
 */
char *get_ip(struct device *nic);

/** 
 * Obtêm o endereço MAC da interface de\n
 * rede, e o retorna.
 * Este nome é alocado dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param nic Estrutura que representa uma das interface\n
 *            de rede do sistema.\n
 *
 * @return um char *, que pode ser:
 * 	       - endereço MAC : quando der tudo certo na obtenção do MAC. 
 * 	       - UNDEFINED_INFO : quando não for possível obter o MAC,\n
 * 	                          porém na prática isso é bastante
 * 	                          improvável. 
 * 	       - NULL : quando houver algum problema mais sério, como\n
 * 	                erro ao tentar alocar memória.
 */
char *get_mac(struct device *nic);

/** 
 * Obtêm o gateway usado pela interface de rede\n
 * rede, e o retorna.
 * Este nome é alocado dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param nic Estrutura que representa uma das interface\n
 *            de rede do sistema.\n
 *
 * @return um char *, que pode ser:
 * 	       - gateway : quando der tudo certo na obtenção do gateway. 
 * 	       - UNDEFINED_INFO : quando não for possível obter o
 * 	                          gateway,\n
 * 	                          porém na prática isso é bastante
 * 	                          improvável. 
 * 	       - NULL : quando houver algum problema mais sério, como\n
 * 	                erro ao tentar alocar memória.
 */
char *get_gateway(struct device *nic);

/** 
 * Obtêm os servidores DNS utilizados pelo sistema, e os retorna.
 * Esta lista de servidores separados por vírgula, é alocada\n
 * dinamicamente, sendo responsabilidade do caller liberar a memória.\n
 *
 * @return um char *, que pode ser:
 * 	       - servidores DNS : quando der tudo certo na obtenção
 * 	                          do servidores DNS 
 * 	       - UNDEFINED_INFO : quando não for possível obter os
 * 	                          servidores\n
 * 	                          porém na prática isso é bastante
 * 	                          improvável. 
 * 	       - NULL : quando houver algum problema mais sério, como\n
 * 	                erro ao tentar alocar memória.
 */
char *get_dns(void);

/** 
 * Obtêm o status link UP da interface de\n
 * rede, e o retorna.
 *
 * O status link UP indica se os módulos do Kernel do Linux\n
 * que tratam da interface de rede, estão carregados. Essa\n
 * informação é útil pois estes módulos precisam estar carregados\n
 * para haver qualquer tipo de conexão com a rede.\n
 * Este status é alocado dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param nic Estrutura que representa uma das interface\n
 *            de rede do sistema.\n
 *
 * @return um char *, que pode ser:
 * 	       - yes : quando o módulo desta interface estiver carregado. 
 * 	       - no : quando ele não estiver carregado, ou quando não\n
 * 	              for possível determinar seu status.
 * @see ifconfig
 */
char *get_link_up(struct device *nic);

/** 
 * Obtêm o status link detected da interface de\n
 * rede, e o retorna.
 *
 * O status link detected indica se há conexão com algum nó\n
 * da rede, ou seja, se o cabo Ethernet está conectado, ou se\n
 * o computador está conectado ao roteador wireless. Essa informação\n
 * é útil para diagnosticar problemas de conexão em um PDV, como\n
 * tendo a simples solução de conectar um cabo, por exemplo.\n
 * A confiabilidade desta informação depende do status link UP\n
 * da interface, pois se o status não estiver UP, o retorna desta\n
 * função pode estar incorreto.\n
 * Este status é alocado dinamicamente, sendo responsabilidade\n
 * do caller liberar a memória.\n
 *
 * @param nic Estrutura que representa uma das interface\n
 *            de rede do sistema.\n
 *
 * @return um char *, que pode ser:
 * 	       - yes : quando o status link detected for confirmado. 
 * 	       - no : quando o status for negativo.
 *
 * @see ethtool
 */
char *get_link_detected(struct device *nic);

#endif	/*__NETWORK_H__*/
