
MODULE_NAME := $(shell basename $(PWD))

PUBLIC_HEADERS := 

INC:=../../inc
BIN:=../../bin
CC = gcc 
CFLAGS = -fPIC -O3 -Wall -pedantic-errors -I/usr/include/boost -I$(INC)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

OBJECTS = 	database_UT.o

.PHONY: default
default: build

.PHONY: build
build: $(OBJECTS)
	$(CC) $(CFLAGS) -o database_UT $(OBJECTS) -lstdc++ -L$(BIN) -ldatabase -L.
	mv database_UT $(BIN)
