CC = gcc

OBJ_c = $(shell find -name "*.c" | sed 's/ /\\ /g')
OBJ_h = $(shell find -name "*.h" | sed 's/ /\\ /g')

CFLAGS = -g -w -lm -pthread $(shell dirname $(OBJ_h) | sed 's/ /\\ /g' | awk '{printf "-I%s ", $$0}')

passgenerator: $(OBJ_c) $(OBJ_h)
	@ $(CC) -o $@ $(OBJ_c) $(CFLAGS)
