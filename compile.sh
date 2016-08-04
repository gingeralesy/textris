#!/bin/bash

set -e

COM_CFLAGS=$(pkg-config --cflags ncurses)
COM_LIBS=$(pkg-config --libs ncurses)

C_FILES=$(ls *.c)
OUTPUT=$(dirname "$0")"/bin/textris"

gcc $COM_CFLAGS -o $OUTPUT $C_FILES $COM_LIBS

