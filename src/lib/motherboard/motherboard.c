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
#include <string.h>

#include <ldc/info.h>
#include <ldc/types.h>
#include <ldc/errors.h>
#include <ldc/dmidecode.h>
#include <ldc/terminal.h>
#include <ldc/string.h>

#include <motherboard/motherboard.h>

int get_info (struct device* device)
{
	struct device *system    = get_system();
	struct device *bios      = get_bios();
	struct device *baseboard = get_baseboard();
	struct device *chassis   = get_chassis();
	
	set_child(device, system);
	set_child(device, bios);
	set_child(device, baseboard);
	set_child(device, chassis);

	return SUCCESS;
}

struct device *get_system()
{
	struct device *dev = new_device ("system");

	char *vendor  = get_dmidecode_keyword_output ("system-manufacturer", 1);
	char *product = get_dmidecode_keyword_output ("system-product-name", 1);
	char *version = get_dmidecode_keyword_output ("system-version", 1);
	char *serial  = get_dmidecode_keyword_output ("system-serial-number", 1);
	char *uuid    = get_dmidecode_keyword_output ("system-uuid", 1);

	struct info_tuple *i_vendor  = new_info_tuple ("Vendor", vendor);
	struct info_tuple *i_product = new_info_tuple ("Product", product);
	struct info_tuple *i_version = new_info_tuple ("Version", version);
	struct info_tuple *i_serial  = new_info_tuple ("Serial Number", serial);
	struct info_tuple *i_uuid    = new_info_tuple ("UUID", uuid);

	add_info (dev, i_vendor);
	add_info (dev, i_product);
	add_info (dev, i_version);
	add_info (dev, i_serial);
	add_info (dev, i_uuid);

	delete (&vendor);
	delete (&product);
	delete (&version);
	delete (&serial);
	delete (&uuid);

	return dev;
}

struct device *get_bios()
{
	struct device *dev = new_device ("bios");

	char *vendor  = get_dmidecode_keyword_output ("bios-vendor", 1);
	char *version = get_dmidecode_keyword_output ("bios-version", 1);
	char *release = get_dmidecode_keyword_output ("bios-release-date", 1);

	struct info_tuple *i_vendor  = new_info_tuple ("Vendor", vendor);
	struct info_tuple *i_version = new_info_tuple ("Version", version);
	struct info_tuple *i_release = new_info_tuple ("Release Date", release);

	add_info (dev, i_vendor);
	add_info (dev, i_version);
	add_info (dev, i_release);

	delete (&vendor);
	delete (&version);
	delete (&release);

	return dev;
}

struct device *get_baseboard()
{
	struct device *dev = new_device ("baseboard");

	char *vendor  = get_dmidecode_keyword_output ("baseboard-manufacturer", 1);
	char *product = get_dmidecode_keyword_output ("baseboard-product-name", 1);
	char *version = get_dmidecode_keyword_output ("baseboard-version", 1);
	char *serial  = get_dmidecode_keyword_output ("baseboard-serial-number", 1);

	struct info_tuple *i_vendor  = new_info_tuple ("Vendor", vendor);
	struct info_tuple *i_product = new_info_tuple ("Product", product);
	struct info_tuple *i_version = new_info_tuple ("Version", version);
	struct info_tuple *i_serial  = new_info_tuple ("Serial Number", serial);

	add_info (dev, i_vendor);
	add_info (dev, i_product);
	add_info (dev, i_version);
	add_info (dev, i_serial);

	delete (&vendor);
	delete (&product);
	delete (&version);
	delete (&serial);

	return dev;
}

struct device *get_chassis()
{
	struct device *dev = new_device ("chassis");

	char *vendor  = get_dmidecode_keyword_output ("chassis-manufacturer", 1);
	char *type    = get_dmidecode_keyword_output ("chassis-type", 1);
	char *version = get_dmidecode_keyword_output ("chassis-version", 1);
	char *serial  = get_dmidecode_keyword_output ("chassis-serial-number", 1);

	struct info_tuple *i_vendor  = new_info_tuple ("Vendor", vendor);
	struct info_tuple *i_type    = new_info_tuple ("Type", type);
	struct info_tuple *i_version = new_info_tuple ("Version", version);
	struct info_tuple *i_serial  = new_info_tuple ("Serial Number", serial);

	add_info (dev, i_vendor);
	add_info (dev, i_type);
	add_info (dev, i_version);
	add_info (dev, i_serial);

	delete (&vendor);
	delete (&type);
	delete (&version);
	delete (&serial);

	return dev;
}

