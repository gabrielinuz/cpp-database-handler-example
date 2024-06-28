#!/bin/bash
#g++ -Wall -std=c++14 -I./include ./lib/libsqlite3.so main.cpp -o ./build/gnu_linux/dbh_example.bin
#g++ -Wall -std=c++14 -I./include ./lib/libsqlite3.so.0.8.6 main.cpp -o ./build/gnu_linux/dbh_example.bin
g++ -o ./build/gnu_linux/dbh_example.bin main.cpp ./lib/libsqlite3.so.0.8.6 -I./include



