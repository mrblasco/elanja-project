#!/bin/bash

find . -type f -iname "*.tex" | rev | sort -r | rev | xargs  kile &

