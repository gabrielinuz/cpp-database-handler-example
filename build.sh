#!/bin/bash

####historico de compilación:
##g++ -Wall -std=c++11 -I./ -lsqlite3 test.cpp -o test.bin
##gcc ./include/vendors/sqlite/shell.c ./include/vendors/sqlite/shell.c -lpthread -ldl
#g++ -Wall -std=c++11 -I./include -lsqlite3 test.cpp -o test.bin

g++ -Wall -std=c++11 -I./include ./lib/libsqlite3.so test.cpp -o test.bin



