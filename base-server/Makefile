# .SILENT

CC=gcc
CC_FLAGS=-Wall -std=c99
CC_DEPS=-Ilib
CC_LIBRARY=-c
CC_OUTPUT=-o

DEPS=obj obj/konet.o
TARGETS=bin obj bin/test
OBJ=obj obj/test.o

# Rules
all: $(TARGETS)
dependences: $(DEPS)
objects: $(OBJ)

bin:
	@mkdir -p bin/

obj:
	@mkdir -p obj/

obj/test.o: test.c
	$(CC) $(CC_DEPS) $(CC_FLAGS) $(CC_LIBRARY) $(CC_OUTPUT) $@ $<

obj/%.o: lib/%.c
	$(CC) $(CC_FLAGS) $(CC_LIBRARY) $(CC_OUTPUT) $@ $<

bin/test: $(OBJ) $(DEPS)
	$(CC) $(CC_FLAGS) $(CC_OUTPUT) $@ obj/*

clean:
	@rm -rf bin/
	@rm -rf obj/
