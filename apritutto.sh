#!/bin/bash

find . -type f -iname "*.sh" -o -iname "*.cc" -o -iname "*.h" | rev | sort -r | rev | xargs  gedit Makefile &

