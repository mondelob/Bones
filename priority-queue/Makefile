#.SILENT:

CXX=g++
CXX_OPTIONS=-Wall -std=c++11
CXX_OUTPUT=-o

CC=gcc
CC_OPTIONS=-Wall -std=c99
CC_OUTPUT=-o

targets=bin bin/test_cpp bin/test_c

all: $(targets)

bin :
	mkdir bin

bin/test_cpp : test.cpp
	$(CXX) $(CXX_OPTIONS) $(CXX_OUTPUT) $@ $<

bin/test_c : test.c
	$(CC) $(CC_OPTIONS) $(CC_OUTPUT) $@ $<

clean:
	rm -rf $(targets)
