#!/bin/bash

find . -type f -iname "*.h" -o -iname "*.cpp" -o -iname "*.cxx" | rev | sort -r | rev | xargs gedit Makefile &

