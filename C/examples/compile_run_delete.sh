#!/usr/bin/sh

gcc $( pkg-config --cflags gtk4 ) example-6.c -o example $( pkg-config --libs gtk4 )
./example
rm example