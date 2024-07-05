#!/bin/bash
##Another options:
#g++ -Wall -std=c++14 -I./include ./lib/libsqlite3.so main.cpp -o ./build/gnu_linux/dbh_example.bin
#g++ -Wall -std=c++14 -I./include ./lib/libsqlite3.so.0.8.6 main.cpp -o ./build/gnu_linux/dbh_example.bin
#g++ -o ./build/gnu_linux/dbh_example.bin main.cpp ./lib/libsqlite3.so.0.8.6 -I./include

##IDEM MSWindows:
g++ -Wall -std=c++14 -I./include -o ./build/gnu_linux/dbh_example.bin main.cpp -L./lib -lsqlite3

cd build/gnu_linux/
chmod +x dbh_example.bin
./dbh_example.bin
