#!/bin/bash

find src -type f -iname "*.h" -o -iname "*.cpp" | rev | sort -r | rev | xargs gedit Makefile &

