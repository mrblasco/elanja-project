#!/bin/bash

find . -type f -iname "*.h" -o -iname "*.c" -o -iname "*.cxx" | rev | sort -r | rev | xargs gedit Makefile &

