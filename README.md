Linux Diagnostics Center
================================================================

The Linux Diagnostic Center (LDC) is a software tool that enables
easy access to hardware information of computers and servers.

-----

Along with the tool, the LDC also provides the libldc, a C library
that allows the developer to obtain hardware information from third
party projects.


Install
----------

To install, use:

```bash
$ make build install
```

Usage
-----
Command example:
```bash
$ sudo ldc -o motherboard -p
```
Output:
```
------motherboard------
------system------
  Vendor: Dell Inc.
  Product: Inspiron 5458
  Version: 01
  Serial Number: 1AAAA11
  UUID: 1A1A1111-1111-1A11-1111-A1A11A111111
------------
------bios------
  Vendor: Dell Inc.
  Version: A05
  Release Date: 08/26/2015
------------
------baseboard------
  Vendor: Dell Inc.
  Product: 1A11A1
  Version: A11
  Serial Number: /1AAAA11/AA1111111A11OZ/
------------
------chassis------
  Vendor: Dell Inc.
  Type: Laptop
  Version: Not Specified
  Serial Number: 1AAAA11
------------
------------
```

Usage options:
```
Linux Diagnostic Center									
Usage: ldc [OPTIONS]										
 -p, --print 		: Prints the devices' informations.
 -h, --help  		: Prints this help message.
 -v, --version 		: Prints LDC version.
 -x, --xml FILE 	: Generates the output in XML format.
 -d, --device DEVICE 	: Includes a device (plugin) in the list of devices.
 -e, --exclude DEVICE	: Excludes a device (plugin) from the list of devices.
 -o, --only DEVICE	: Generates the output of a single device.
 -s, --single-process	: Runs LDC using a single process (allows XML output mode).

DEVICE: processor, memory, network, harddisk, motherboard, software.				
	 											
The command line options overrides the options in the configuration file.
See file ldc/src/ldc.conf for default options.
```

Dependencies
------------

LDC runs independent from the required dependencies, because
plugins are executed individually. The absence of a dependency
affects only the plugin that uses that dependency.

LDC is designed to work with:
- dmidecode
- libparted
- libc


Contributors
------------

List of contributors of the project.

- Adriano Melo <astm@cin.ufpe.br>
- Hugo Alencar <hraa@cin.ufpe.br>
- Dayvid Victor <dvro@cin.ufpe.br>
- Thyago Porpino <tnp@cin.ufpe.br>

