#.SILENT:

CC=gcc
CC_OPTIONS=-Wall -std=c99
CC_OUTPUT=-o

targets=bin bin/test

all: $(targets)

bin :
	mkdir bin

bin/test : test.c
	$(CC) $(CC_OPTIONS) $(CC_OUTPUT) $@ $<

clean:
	rm -rf $(targets)
