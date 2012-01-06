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


#include <stdlib.h>
#include <stdio.h>

#include <ldc/parser.h>
#include <ldc/string.h>

#include <translator.h>

/* carrega todos os pares CHAVE=VALOR do arquivo de tradução
 * numa hash_table, para eliminar a necessidade de abrir varias
 * vezes o arquivo. */
hash_table *load_translation()
{
	char *filename;
	hash_table *trans = NULL;	
	FILE *fp;
	char buffer[256];
	int buf_size;

	/* obter a localização do arquivo de tradução no ldc.conf */
	filename = TRANSLATION_FILE;

	if (filename == NULL)
		return NULL;	
	
	if ((fp = fopen(filename, "r")) == NULL)
		return NULL;

	/* criar hash_table para armazenar as tuplas de tradução */	
	trans = new_hash_table(); 

	buf_size = sizeof(buffer)/sizeof(buffer[0]);

	while (fgets(buffer, buf_size, fp) != NULL) {
		struct tuple *tmp = parse_tuple(buffer);
		
		if (tmp != NULL)
			add_hash_info(trans, tmp->key, tmp->value);
		
		free_tuple (&tmp);
	}

	fclose(fp);

	return trans;
}

char *get_translation(hash_table *translation, char *label)
{	
	if (translation == NULL || label == NULL)
		return NULL;	

	return get_hash_info(translation, label);	
}
