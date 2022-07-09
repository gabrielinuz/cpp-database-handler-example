#!/bin/bash
g++ -Wall -std=c++11 -I./include ./lib/libsqlite3.so use_example.cpp -o use_example.bin
g++ -Wall -std=c++11 -I./include ./lib/libsqlite3.so use_example_refact.cpp -o use_example_refact.bin



