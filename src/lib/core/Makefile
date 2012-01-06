include Rules.make

prefix=/usr

BIN=../../../bin
SRC=../..
TEST=../../../tests

CC=gcc -c
GCC=gcc
CFLAGS=-Wall -g -I.. -I$(SRC)/include -fPIC $(EFLAGS) -m32 -DPREFIX=$(prefix)
LDFLAGS=-Wall -g -L$(BIN) -lldc$(NAME) -I.. -I$(SRC)/include $(EFLAGS) -m32

all: build test

build: $(OBJS)
	$(GCC) $(OBJS) -shared -Wl,-soname,libldc$(NAME).so.$(MAJOR_NUMBER) -o $(BIN)/libldc$(NAME).so.$(MAJOR_NUMBER).$(MINOR_NUMBER) -lc -L $(BIN) -fPIC -m32
	@ln -sf libldc$(NAME).so.$(MAJOR_NUMBER).$(MINOR_NUMBER) $(BIN)/libldc$(NAME).so.$(MAJOR_NUMBER)
	@ln -sf libldc$(NAME).so.$(MAJOR_NUMBER) $(BIN)/libldc$(NAME).so

test: $(OBJS)
	$(GCC) $(LDFLAGS) -o $(TEST)/bin/test_$(NAME) $(TEST)/lib/main_$(NAME).c -lcheck

.c.o:
	$(CC) $(CFLAGS) $<

clean:
	$(RM) *.o

