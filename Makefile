CC=gcc
CFLAGS=-Wall -Wextra -g
SRC=src/

all: $(SRC)*.c
	$(CC) $(CFLAGS) $? -o ucc
	
