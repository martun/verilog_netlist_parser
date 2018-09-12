
MODULE_NAME := database #$(shell basename $(PWD))

PUBLIC_HEADERS := instance_port.hpp module_description.hpp module_instance.hpp module_port.hpp net.hpp netlist.hpp port.hpp netlist_builder.hpp 

INC:=../../inc
BIN:=../../bin
CC = gcc 
CFLAGS = -fPIC -O3 -Wall -pedantic-errors -I/usr/include/boost -I$(INC)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

OBJECTS = 	instance_port.o \
			module_description.o \
			module_instance.o \
			module_port.o \
			net.o \
			netlist.o \
			port.o \
			netlist_builder.o \
			netlist_keywords.o

.PHONY: default
default: build

.PHONY: build
build: copy_public_include_files $(OBJECTS)
	$(CC) $(CFLAGS) -o libdatabase.so $(OBJECTS) -lstdc++ -shared
	cp -rf libdatabase.so $(BIN)

.PHONY: copy_public_include_files
copy_public_include_files : 
	mkdir -p $(INC)/$(MODULE_NAME)
	cp $(PUBLIC_HEADERS) $(INC)/$(MODULE_NAME)

