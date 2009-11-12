#!/bin/bash

find . -type f -iname "*.h" -o -iname "*.c" | rev | sort -r | rev | xargs gedit Makefile &

