#!/bin/bash

prefix=/usr

all: build


install: script 
	mkdir -p $(prefix)/share/ldc
	mkdir -p $(prefix)/etc
	mkdir -p $(prefix)/lib
	cp bin/ldc-bin $(prefix)/bin/ldc-bin
	cp src/pt_BR $(prefix)/share/ldc/pt_BR
	cp src/ldc.conf $(prefix)/etc/ldc.conf
	cp -P bin/*.so* $(prefix)/lib/

script:
	mkdir -p $(prefix)/bin
	@echo "#!/bin/bash" > $(prefix)/bin/ldc
	@echo "export LIBC_FATAL_STDERR_=1" >> $(prefix)/bin/ldc
	@echo "export LD_LIBRARY_PATH=$(prefix)/lib" >> $(prefix)/bin/ldc
	@echo "$(prefix)/bin/ldc-bin \$$* 2> /dev/null" >> $(prefix)/bin/ldc
	chmod a+x $(prefix)/bin/ldc
ifneq "$(prefix)" "/usr"
	ln -sf $(prefix)/bin/ldc /usr/bin/ldc
endif

install_redhat:
	cp -R scripts/redhat/* /etc/init.d/
	/sbin/chkconfig --add ldc-daemon

install_librix:
	cp -R scripts/librix/* /etc/init.d/
	rc-update add ldc-daemon default

install_debian:
	cp -R scripts/debian/* /etc/init.d/
	update-rc.d ldc-daemon defaults

uninstall:
	rm -fr $(prefix)/bin/ldc*
	rm -fr /usr/bin/ldc*
	rm -fr $(prefix)/lib/libldc*
	rm -fr $(prefix)/share/ldc
	rm -fr /etc/init.d/ldc-*

clean:
	rm -f bin/*so*
	rm -f bin/ldc*
	rm -f tests/bin/exec_*
	rm -f tests/bin/test_*
	rm -f *.cfg
	rm -fr doc/Doxygen
	@(cd src; make clean)
	@(cd src/lib; make clean)

build:
	@(cd src/lib; make build prefix=$(prefix);)
	@(cd src; make build prefix=$(prefix))

test: 
	@(cd src/lib; make test;)
	@(cd src; make test;)
	@(export LD_LIBRARY_PATH=/usr/lib:bin:tests/bin; ./bin/ldc-bin)
	@for i in `echo tests/bin/test*`; do \
		if [ -f $$i ]; then \
			(export LD_LIBRARY_PATH=/usr/lib:bin:tests/bin; ./$$i; echo ""); \
		fi; \
	done

docs:
	doxygen doc/doxygen.conf;
	cp -v doc/Doxygen/man/man3/* $(prefix)/share/man/man3/;

