#!/bin/bash

let m=$1/2
#sed -e "s/n <- [0-9][0-9]*;/n <- $1;/g" -e "s/color <- c(rep(3,[0-9][0-9]*), rep(2,[0-9][0-9]*));/color <- c(rep(3,$m), rep(2,$m));/g" -i commandsR.txt 

sed -e "s/dim(a) <- c([0-9][0-9]*,[0-9][0-9]*);/dim(a) <- c($1,$1);/g" -e "s/color <- c(rep(3,[0-9][0-9]*), rep(2,[0-9][0-9]*));/color <- c(rep(3,$m), rep(2,$m));/g" -i commandsR.txt 

R --no-save <commandsR.txt > /dev/null

eog pippo.png

