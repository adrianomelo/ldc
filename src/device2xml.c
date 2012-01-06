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


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <ldc/types.h>
#include <ldc/errors.h>
#include <ldc/terminal.h>
#include <ldc/string.h>
#include <ldc/file.h>

#include <device2xml.h>

int device2xml (struct device *device, hash_table *config)
{
	if (device == NULL)
		return ERROR;

	char *xml_filename = get_hash_info (config, "xml_output");
	
	if (is_blank(xml_filename)) {
		char *xml_tmp = "/tmp/ldc.xml";
		delete(&xml_filename);
		xml_filename = get_clone(xml_tmp);
	}
	
	char *dev_name = device->name;
	
	if ( !is_blank(dev_name) && !equals(dev_name, "computer") ) {
		char *clean_str = get_clean_string(xml_filename,".xml");
		int len = strlen(clean_str) + strlen(dev_name) + 6;
		char *xml_tmp = calloc(len, sizeof(char));
		//sprintf(xml_tmp, "%s_%s.xml", clean_str, dev_name);
		append_string(&xml_tmp, clean_str);
		append_string(&xml_tmp, "_");
		append_string(&xml_tmp, dev_name);
		append_string(&xml_tmp, ".xml");
		delete(&xml_filename);
		xml_filename = get_clone(xml_tmp);
		delete(&xml_tmp);
		delete(&clean_str);
	}

	char *XML = append_xml_meta (device);
	
	write_output (XML, xml_filename, "w");

	delete (&XML);
	delete (&xml_filename);

	return SUCCESS;
}

char *append_xml_meta (struct device* device)
{
	char *output = NULL;
	
	char *header  = "<?xml version=\"1.0\" encoding=\"ISO-8859-2\"?>\n";
	char *content = "<device></device>\n";
	
	char *tmp_content = append_xml_device (device);
	
	if (tmp_content == NULL){
		int output_size = strlen(header) + strlen(content) + 1;

		output = calloc (output_size, sizeof(char));
		sprintf(output, "%s%s", header, content);

		return output;
	}
	
	int output_size = strlen(header) + strlen(tmp_content) + 1;

	output = calloc (output_size, sizeof(char));
	sprintf(output, "%s%s", header, tmp_content);

	delete (&tmp_content);

	return output;
}

char *append_xml_device (struct device *device)
{
	if (device == NULL)
		return NULL;

	if (device->name == NULL)
		return NULL;

	char *template = "<device name=\"\">\n</device>\n";
	char *name = device->name;

	char *child  = NULL;
	char *next   = NULL;
	char *info   = NULL;
	
	char *output = NULL;
	int output_size = strlen(name) + strlen(template) + 1;

	if (device->info != NULL){
		info = append_xml_info_tuple (device->info);
		
		if (info != NULL)
			output_size = output_size + strlen(info);
	}

	if (device->child != NULL) {
		child = append_xml_device (device->child);

		if (child != NULL)
			output_size = output_size + strlen(child);
	}

	if (device->next != NULL) {
		next = append_xml_device (device->next);
		
		if (next != NULL)
			output_size = output_size + strlen(next);
	}

	output = calloc (output_size + 1, sizeof(char));

	sprintf(output, "<device name=\"%s\">\n", name);

	if (info != NULL)
		strcat(output, info);

	if (child != NULL)
		strcat(output, child);

	strcat(output, "</device>\n");

	if (next != NULL)
		strcat(output, next);

	delete (&info);
	delete (&child);
	delete (&next);

	return output;
}

char *append_xml_info_tuple (struct info_tuple *info)
{
	if (info == NULL)
		return NULL;

	char *output = NULL;	
	char *next   = NULL;

	if (info->next != NULL)
		 next = append_xml_info_tuple (info->next);

	char *key   = get_info_tuple_key (info);
	char *value = get_info_tuple_value (info);

	/* há uma inconsistência na tupla atual mas existe um next */
	if ((key == NULL || value == NULL) && next != NULL)
		return next;

	char *template = "<info key=\"\" value=\"\" />\n";
	int output_size = strlen(key) + strlen(value) + strlen(template) + 1;

	if (next == NULL) {
		output = calloc (output_size, sizeof(char));
	} else {
		output_size = output_size + strlen(next);
		output = calloc (output_size, sizeof(char));
	}

	char *value_filtered = get_clean_string (value, "\"");

	sprintf (output, "<info key=\"%s\" value=\"%s\" />\n", key, value_filtered);
	
	if (next != NULL)
		strcat (output, next);

	delete (&next);
	delete (&value_filtered);

	return output;
}

