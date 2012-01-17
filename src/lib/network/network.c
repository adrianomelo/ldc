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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ldc/types.h>
#include <ldc/info.h>
#include <ldc/terminal.h>
#include <ldc/errors.h>
#include <ldc/string.h>
#include <ldc/system.h>

#include <network/network.h>


int get_info(struct device *network)
{
	if (network == NULL)
		return ERROR;

	int status = get_interfaces(network);

	if (status == SUCCESS) {
		struct device *iter = network->child;

		while (iter) {
			status = add_nic_info(iter);
			iter = iter->next;
		}
	}

	return status;
}

int get_interfaces(struct device *network)
{
	if (network == NULL)
		return ERROR;

	FILE *fp = NULL;
	char cmd[CMD_SIZE];
	char buffer[BUF_SIZE];
	int status = SUCCESS;

	char *temp = "%s -a | grep 'HW' |"
			" grep -E 'eth|wlan' |" " awk '{print $1}'";

	char *cmd_path = which("ifconfig");

	if (cmd_path == NULL)
		return ERROR;

	sprintf(cmd, temp, cmd_path); 

	delete(&cmd_path);


	fp = open_cmd_stream(cmd);

	if (fp == NULL)
		return ERROR;

	while (fgets(buffer, BUF_SIZE, fp) != NULL) {
		char *name = strip_end(buffer, "");
		char *type = NULL;

		if (strstr(name, "eth") != NULL)
			type = "ethernet";
		else
			type = "wireless";

		struct device *nic = new_device(type);
		set_child(network, nic);

		add_info(nic, new_info_tuple("Interface", name));
		delete(&name);
	}

	status = close_cmd_stream(&fp);

	if (status == SUCCESS && !is_blank(buffer))
		status = SUCCESS;
	else
		status = ERROR;

	return status;
}

int add_nic_info(struct device *nic)
{
	if (nic == NULL)
		return ERROR;

	char *vendor = get_vendor(nic);
	add_info(nic, new_info_tuple("Vendor", vendor));
	delete(&vendor);

	char *model = get_model(nic);
	add_info(nic, new_info_tuple("Model", model));
	delete(&model);

	char *ip = get_ip(nic);
	add_info(nic, new_info_tuple("IP Address", ip));
	delete(&ip);

	char *mac = get_mac(nic);
	add_info(nic, new_info_tuple("MAC Address", mac));
	delete(&mac);

	char *gw = get_gateway(nic);
	add_info(nic, new_info_tuple("Gateway", gw));
	delete(&gw);

	char *dns = get_dns();
	add_info(nic, new_info_tuple("DNS Servers", dns));
	delete(&dns);

	char *link_up = get_link_up(nic);
	add_info(nic, new_info_tuple("Link UP", link_up));

	/* O link detected só apresenta uma
	   informação confiável se o link estiver UP */
	if (link_up != NULL && strcmp(link_up, "yes") == 0) {
		char *link_det = get_link_detected(nic);
		add_info(nic, new_info_tuple("Link Detected", link_det));
		delete(&link_det);
	}

	delete(&link_up);

	return SUCCESS;
}

char *get_ip(struct device *nic)
{
	if (nic == NULL)
		return NULL;	

	char *cmd_path;	
	char *output;
	char command[CMD_SIZE];
	
	char *temp = "%s -a %s | grep 'Bcast' | awk "
			"'BEGIN {FS=\":\"} ; {print $2}' | awk '{print $1}'";

	cmd_path = which("ifconfig");
	
	if (cmd_path == NULL)
		return get_undefined_info();	

	sprintf(command, temp, cmd_path, nic->info->value);
	output = get_cmd_output(command, BUF_SIZE);
	delete(&cmd_path);

	if (output == NULL)
		return get_undefined_info();

	return output;
}

char *get_mac(struct device *nic)
{
	if (nic == NULL)
		return NULL;	

	char *cmd_path;	
	char *output;
	char command[CMD_SIZE];
	
	char *temp = "%s %s | grep 'HW' | awk '{print $NF}'";

	cmd_path = which("ifconfig");
	
	if (cmd_path == NULL)
		return get_undefined_info();	

	sprintf(command, temp, cmd_path, nic->info->value);
	output = get_cmd_output(command, BUF_SIZE);
	delete(&cmd_path);

	if (output == NULL)
		return get_undefined_info();

	return output;
}

char *get_gateway(struct device *nic)
{
	if (nic == NULL)
		return NULL;

	char *cmd_path;	
	char *output;
	char command[CMD_SIZE];
	
	char *temp = "%s -n | grep %s | grep G | awk '{print $2}'";

	cmd_path = which("route");

	if (cmd_path == NULL)
		return get_undefined_info();	

	sprintf(command, temp, cmd_path, nic->info->value);
	output = get_cmd_output(command, BUF_SIZE);
	delete(&cmd_path);

	if (output == NULL)
		return get_undefined_info();

	return output;
}

char *get_dns(void)
{
	char line_buffer[BUF_SIZE];
	FILE *fp = NULL;
	char *output = NULL;
	char *rem = NULL;
	char *clean = NULL;
	int status = 0;

	char command[] = "cat /etc/resolv.conf | grep nameserver |"
	    "grep -v '#' |" " awk '{print $2}'";

	fp = open_cmd_stream(command);

	if (fp == NULL)
		return NULL;

	rem = calloc(MAX_DNS_NUM * BUF_SIZE, sizeof(char));

	int i = 0;
	while (fgets(line_buffer, BUF_SIZE, fp) != NULL && i < MAX_DNS_NUM) {
		char *temp = strip_end(line_buffer, "");
		strncat(rem, temp, strlen(temp));
		strncat(rem, ", ", 2);
		delete(&temp);
		++i;
	}

	clean = strip_end(rem, ",");
	delete(&rem);

	/* pegando o status do comando que foi executado */
	status = close_cmd_stream(&fp);

	/* não retornamos strings 'vazias' */
	if (status == SUCCESS && !is_blank(clean)) {
		output = clean;
	} else {
		delete(&clean);
		output = calloc(BUF_SIZE, sizeof(char));
		copy_string(output, UNDEFINED_INFO, BUF_SIZE);
	}
	return output;

}

char *get_link_up(struct device *nic)
{
	if (nic == NULL)
		return NULL;

	char *cmd_path;	
	char *output;
	char command[CMD_SIZE];
	
	char *temp = "%s %s | grep UP | awk '{print $1}'";

	cmd_path = which("ifconfig");

	if (cmd_path == NULL)
		return get_undefined_info();	

	sprintf(command, temp, cmd_path, nic->info->value);
	output = get_cmd_output(command, BUF_SIZE);

	char *cmd_output = get_cmd_output(command, BUF_SIZE);
	delete(&cmd_path);

	if (cmd_output == NULL)
		return get_undefined_info();

	delete(&output);
	output = calloc(4, sizeof(char));
	
	if (output == NULL)
		return get_undefined_info();


	if (cmd_output != NULL && strcmp(cmd_output, "UP") == 0)
		copy_string(output, "yes", 4);
	else
		copy_string(output, "no", 3);

	delete(&cmd_output);
	return output;
}

char *get_vendor(struct device *nic)
{
	if (nic == NULL)
		return NULL;	

	char command[2*CMD_SIZE];
	char *output = NULL;
	char *type = NULL;
	
	char *temp = "%s -m | grep %s |  awk "
			"'BEGIN {FS = \"\\\"\" } ; { print $4 }'";

	char *cmd_path = which("lspci");

	if (cmd_path == NULL)
		return get_undefined_info();

	/* checando o tipo de interface de rede */
	if (strstr(nic->name, "ethernet") != NULL)
		type = "'Ethernet controller'";
	else if (strstr(nic->name, "wireless") != NULL)
		type = "'Network controller'";
	else
		return get_undefined_info();

	sprintf(command, temp, cmd_path, type);
	output = get_cmd_output(command, BUF_SIZE);

	if (output == NULL)
		return get_undefined_info();

	delete(&cmd_path);
	return output;
}

char *get_model(struct device *nic)
{
	if (nic == NULL)
		return NULL;	

	char command[2*CMD_SIZE];
	char *output = NULL;
	char *type = NULL;
	
	char *temp = "%s -m | grep %s |  awk 'BEGIN {FS = \"\\\"\" } ; { print $6 }'";

	char *cmd_path = which("lspci");

	if (cmd_path == NULL)
		return get_undefined_info();

	/* checando o tipo de interface de rede */
	if (strstr(nic->name, "ethernet") != NULL)
		type = "'Ethernet controller'";
	else if (strstr(nic->name, "wireless") != NULL)
		type = "'Network controller'";
	else
		return get_undefined_info();

	sprintf(command, temp, cmd_path, type);
	output = get_cmd_output(command, BUF_SIZE);

	if (output == NULL)
		return get_undefined_info();

	delete(&cmd_path);
	return output;
}

char *get_link_detected(struct device *nic)
{
	if (nic == NULL)
		return NULL;

	char command[CMD_SIZE];
	char *output;
	char *cmd_path;

	char *temp = "%s %s | grep 'Link detected' | awk '{print $3}'";

	cmd_path = which("ethtool");

	if (cmd_path == NULL)
		return get_undefined_info();

	sprintf(command, temp, cmd_path, nic->info->value);
	output = get_cmd_output(command, BUF_SIZE);

	if (output == NULL)
		return get_undefined_info();
	
	delete(&cmd_path);
	return output;
}
