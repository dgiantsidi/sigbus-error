CC = gcc
FLAGS = -Wall -g
LDFLAGS = -lrt

.PHONY = all clean

all: clean main

main: main.c
	$(CC) $(FLAGS) -o $@ $< $(LDFLAGS)

clean:
	-rm -f main
