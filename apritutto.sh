#!/bin/bash

find . -type f -iname "*.sh" -o -iname "*.cc" | rev | sort -r | rev | xargs  gedit Makefile &

