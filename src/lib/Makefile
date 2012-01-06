prefix=/usr

all:
	@(cd core; make all prefix=$(prefix))
	@for i in `echo *`; do \
		if [ -d $$i ]; then \
			if [ -f $$i/Makefile ]; then \
				(cd $$i; make all) \
			fi; \
		fi; \
	done

build:
	@(cd core; make build prefix=$(prefix);)
	@for i in `echo *`; do \
		if [ -d $$i ]; then \
			if [ -f $$i/Makefile ]; then \
				(cd $$i; make build) \
			fi; \
		fi; \
	done

test:
	@for i in `echo *`; do \
		if [ -d $$i ]; then \
			if [ -f $$i/Makefile ]; then \
				(cd $$i; make test) \
			fi; \
		fi; \
	done

clean:
	@for i in `echo *`; do \
		if [ -d $$i ]; then \
			if [ -f $$i/Makefile ]; then \
				(cd $$i; make clean) \
			fi; \
		fi; \
	done \
