#!/bin/bash

g++ -Wall -Wextra -pedantic-errors $( pkg-config --cflags gtk4 ) main.cpp $( pkg-config --libs gtk4 ) -o nsuluofuo
