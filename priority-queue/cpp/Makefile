#.SILENT:

CXX=g++
CXX_OPTIONS=-Wall -std=c++11
CXX_OUTPUT=-o

targets=bin bin/test

all: $(targets)

bin :
	mkdir bin

bin/test : test.cpp
	$(CXX) $(CXX_OPTIONS) $(CXX_OUTPUT) $@ $<

clean:
	rm -rf $(targets)
