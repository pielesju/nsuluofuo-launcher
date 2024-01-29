#!/bin/bash

g++ $( pkg-config --cflags gtk4 ) main.cpp $( pkg-config --libs gtk4 ) -o nsuluofuo
