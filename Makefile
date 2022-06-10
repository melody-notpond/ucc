CC=gcc
CFLAGS=-Wall -Wextra -g -Iinclude/
SRC=src/

all: $(SRC)*.c
	$(CC) $(CFLAGS) $? -o ucc
	
