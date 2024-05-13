CC = gcc
CFLAGS = -I. -g -w -lm -pthread
OBJ_c = $(wildcard *.c)
OBJ_h = $(wildcard *.h)
OBJ_o = $(patsubst %.c , %.o , $(OBJ_c))

passgenerator: $(OBJ_o) $(OBJ_h)
	$(CC) -o $@ $(OBJ_o) $(CFLAGS)

