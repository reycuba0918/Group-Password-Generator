CC = gcc

OBJ_c = $(shell find -name "*.c" | sed 's/ /\\ /g')
OBJ_h = $(shell find -name "*.h" | sed 's/ /\\ /g')

CFLAGS = -g $(shell dirname $(OBJ_h) | sed 's/ /\\ /g' | awk '{printf "-I%s ", $$0}') -lm -pthread

passgenerator: $(OBJ_c) $(OBJ_h)
	@ $(CC) -o $@ $(OBJ_c) $(CFLAGS)
