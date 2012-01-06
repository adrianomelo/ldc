
prefix=/usr

BIN=../bin
TEST=../tests

GCC=gcc
CC=gcc -c
RM=rm -f

LDFLAGS=-ldl -lldccore -g -Wall -L$(BIN) -m32 -DPREFIX=$(prefix)
CFLAGS=-g -Wall -Iinclude -m32 -DPREFIX=$(prefix)

COMMON_OBJS=device2xml.o filelist.o libraries.o translator.o arguments.o

LDC_OBJS=$(COMMON_OBJS) ldc.o

all: build

build: $(LDC_OBJS)
	$(GCC) $(LDC_OBJS) $(LDFLAGS) -o $(BIN)/ldc-bin

.c.o:
	$(CC) $(CFLAGS) $<

test:
	$(GCC) $(COMMON_OBJS) $(CFLAGS) $(LDFLAGS) -o $(TEST)/bin/test_ldc $(TEST)/ldc/ldc.c -lcheck

clean:
	$(RM) *.o
