#!/bin/bash

if [ $5 ]
then 
	for i in `seq 1 $5`
	do
		./main $1 $2 $3
	done

	rm -rf net.png
	rm -rf comp.png
	rm -rf degree.png

	command=$4
	case $4 in
		'-net')		sed -e "s/n <- [0-9][0-9]*;/n <- $1;/g" -e "s/t <- [0-9][0-9]*;/t <- $2;/g" -i commandsNET.txt;
				R --no-save <commandsNET.txt > /dev/null;
				eog net.png &;;

		'-composition')	sed -e "s/n <- [0-9][0-9]*;/n <- $1;/g" -e "s/t <- [0-9][0-9]*;/t <- $2;/g" -i commandsCOMP.txt;
				R --no-save <commandsCOMP.txt > /dev/null;
				eog comp.png &;;
			
		'-degree')	sed -e "s/n <- [0-9][0-9]*;/n <- $1;/g" -e "s/t <- [0-9][0-9]*;/t <- $2;/g" -i commandsDEGREE.txt;
				R --no-save <commandsDEGREE.txt > /dev/null;
				eog degree.png &;;

		'-all')		sed -e "s/n <- [0-9][0-9]*;/n <- $1;/g" -e "s/t <- [0-9][0-9]*;/t <- $2;/g" -i commandsNET.txt;
				R --no-save <commandsNET.txt > /dev/null;
				sed -e "s/n <- [0-9][0-9]*;/n <- $1;/g" -e "s/t <- [0-9][0-9]*;/t <- $2;/g" -i commandsCOMP.txt;
				R --no-save <commandsCOMP.txt > /dev/null;
				sed -e "s/n <- [0-9][0-9]*;/n <- $1;/g" -e "s/t <- [0-9][0-9]*;/t <- $2;/g" -i commandsDEGREE.txt;
				R --no-save <commandsDEGREE.txt > /dev/null;
				eog net.png &;;
		*)		echo "bad arguments use: <n agents> <n iterations> <distance neighborhood> <option> <n simulations>";
				echo "wrong option:";
				echo "			-composition	for degree composition";
				echo "			-degree		for number of links";
				echo "			-net 		for net topology";
				echo "			-all		for all the graphics";;
	esac
else
	echo "bad arguments use: <n agents> <n iterations> <distance neighborhood> <option> <n simulations>"
	echo "				-missing number of simulation"
fi

