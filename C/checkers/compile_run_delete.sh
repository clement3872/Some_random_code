#!/usr/bin/sh

# Note that the Makefile does baasicly the same things


INPUTS=*.c
OUTPUT=application

gcc $( pkg-config --cflags gtk4 ) -o $OUTPUT $INPUTS $( pkg-config --libs gtk4 )

# Here is another way to compile:
# gcc `pkg-config --cflags gtk4` -o $OUTPUT $INPUTS `pkg-config --libs gtk4`

./$OUTPUT
rm $OUTPUT