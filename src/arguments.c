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
#include <getopt.h>

#include <arguments.h>
#include <ldc/config.h>
#include <ldc/hashtable.h>

#include <ldc/types.h>
#include <ldc/errors.h>
#include <ldc/string.h>


int load_options(hash_table *table, int argc, char *argv[])
{
	if (table == NULL)
		return ERROR;

	if (argc == 0)
		return SUCCESS;

	int c;
	while(1) {
		static struct option long_options[] = 
		{
			{"xml", required_argument, 0, 'x'},
			{"version", no_argument, 0, 'v'},
			{"help", no_argument, 0, 'h'},
			{"print", no_argument, 0, 'p'},
			{"device", required_argument, 0, 'd'},
			{"exclude", required_argument, 0, 'e'},
			{"only", required_argument, 0, 'o'},
			{"single-process", no_argument, 0, 's'},
			{"fun", no_argument, 0, 'f'},
			{0, 0, 0, 0}
		};
	
		int option_index = 0;
	
		c = getopt_long (argc, argv, "x:vhpd:e:o:sf", long_options, &option_index);

		if (c == -1)
			break;

		if (c == '?' || c == ':') {
			print_syntax_error();
			return ERROR;
		}


		switch (c) {
		
		case 0:
			if (long_options[option_index].flag != 0)
				break;

			printf("option: %s ", long_options[option_index].name);
			if (optarg)
				printf("arg: %s", optarg);
			printf("\n");
			break;
	
		case 'p':
			add_hash_info(table,"print_output", "yes");
			break;
	
		case 'x':
			if (optarg) {
				add_hash_info(table, "xml_output", optarg);
			} else {
				print_syntax_error();
				return ERROR;
			}
			break;
	
		case 'h':
			print_help();
			exit(0);
			break;
	
		case 'f':
			print_fun();
			exit(0);
			break;
	
		case 'v':
			print_version();
			exit(0);
			break;
	
		case 'd':
			if (optarg == NULL || !is_valid_plugin(optarg)) {
				print_syntax_error();
				return ERROR;
			}

			if(equals(optarg, "all")) {
				add_hash_info(table, "all_plugins", "yes");
			} else {
				add_hash_info(table, optarg, "yes");
			}

			break;

		case 'e':
			if (optarg == NULL || !is_valid_plugin(optarg) || equals(optarg, "all")) {
				print_syntax_error();
				return ERROR;
			}
			
			add_hash_info(table, optarg, "no");
			
			break;

		case 'o':
			if (optarg == NULL || !is_valid_plugin(optarg)) {
				return ERROR;
			}

			add_hash_info(table,"only",optarg);

			break;

		case 's':
			add_hash_info(table,"single","yes");
			break;

		}

	}

	return SUCCESS;	
}

void print_help()
{
	printf("Linux Diagnostic Center										\n");
	printf("Usage: ldc [OPTIONS]										\n");
	printf(" -p, --print            : Prints the devices' informations.					\n");
	printf(" -h, --help             : Prints this help message.						\n");
	printf(" -v, --version          : Prints LDC version.							\n");
	printf(" -x, --xml FILE         : Generates the output in XML format.					\n");
	printf(" -d, --device DEVICE    : Includes a device (plugin) in the list of devices.			\n");
	printf(" -e, --exclude DEVICE   : Excludes a device (plugin) from the list of devices.			\n");
	printf(" -o, --only DEVICE      : Generates the output of a single device.				\n");
	printf(" -s, --single-process   : Runs LDC using a single process (allows XML output mode).		\n");
	printf("												\n");
	printf("DEVICE: processor, memory, network, harddisk, motherboard, software.				\n");
	printf("												\n");
	printf("The command line options overrides the options in the configuration file.			\n");
	printf("See file ldc/src/ldc.conf for default options.							\n\n");
}

void print_version()
{
	printf("Version: LDC 1.0\n");
}

void print_syntax_error()
{
	printf("\n");
	printf("ldc: invalid option.				\n");
	printf("Try 'ldc --help' for more information.		\n");
	printf("\n");
}

int is_valid_plugin(char *name)
{
	return 1;
}

void print_fun()
{
	printf("\n\n");
	printf("\t\t*****************************\n");
	printf("\t\t*                           *\n");
	printf("\t\t*    #      ####    ####    *\n");
	printf("\t\t*    #      #   #  #        *\n");
	printf("\t\t*    #      #   #  #        *\n");
	printf("\t\t*    #      #   #  #        *\n");
	printf("\t\t*    #####  ####    ####    *\n");
	printf("\t\t*                           *\n");
	printf("\t\t*   - Adriano Melo          *\n");
	printf("\t\t*   - Alexandre Barreiras   *\n");
	printf("\t\t*   - Dayvid Victor         *\n");
	printf("\t\t*   - Elifrancis Soares     *\n");
	printf("\t\t*   - Guilherme Dantas      *\n");
	printf("\t\t*   - Hugo Alencar          *\n");
	printf("\t\t*   - Thyago Porpino        *\n");
	printf("\t\t*                           *\n");
	printf("\t\t*****************************\n");
	printf("\n\n");

}

