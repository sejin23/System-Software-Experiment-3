#!/bin/bash
mkdir -p "result"

if [ $1 = 'resource' ]
then
	mkdir -p "./result/resource"
	if [ $2 = 'book' ]
	then
		touch "./result/resource/$2.dat"
	elif [ $2 = 'e-book' ]
	then
		
	elif [ $2 = 'magazine' ]
	then
		
	elif [ $2 = 'all' ]
	then
		
	fi
elif [ $1 = 'input' ]
then
	mkdir -p "./result/input"
elif [ $1 = 'space' ]
then
	mkdir -p "./result/space"
elif [ $1 = 'output' ]
then
	mkdir -p "./result/output"
fi
