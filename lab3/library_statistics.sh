#!/bin/bash
make
mkdir -p "result"
if [ $1 = 'resource' ]
then
	mkdir -p "./result/resource"
	if [ $2 = 'book' ]
	then
		echo $'Type\tName' > ./result/resource/book.dat
		awk '{print}' ./resource.dat | while read -a dat
		do
			if [ "${dat[0]}" == "Book" ]
			then
				echo ${dat[0]}$'\t'${dat[1]} >> ./result/resource/book.dat
			fi
		done
	elif [ $2 = 'magazine' ]
	then
		echo $'Type\tName' > ./result/resource/magazine.dat
		awk '{print}' ./resource.dat | while read -a dat
		do
			if [ "${dat[0]}" == "Magazine" ]
			then
				echo ${dat[0]}$'\t'${dat[1]} >> ./result/resource/magazine.dat
			fi
		done
	elif [ $2 = 'e-book' ]
	then
		echo $'Type\tName' > ./result/resource/e-book.dat
		awk '{print}' ./resource.dat | while read -a dat
		do
			if [ "${dat[0]}" == "E-book" ]
			then
				echo ${dat[0]}$'\t'${dat[1]} >> ./result/resource/e-book.dat
			fi
		done
	elif [ $2 = 'all' ]
	then
		echo $'Type\tName' > ./result/resource/book.dat
		echo $'Type\tName' > ./result/resource/magazine.dat
		echo $'Type\tName' > ./result/resource/e-book.dat
		awk '{print}' ./resource.dat | while read -a dat
		do
			if [ "${dat[0]}" == "Book" ]
			then
				echo ${dat[0]}$'\t'${dat[1]} >> ./result/resource/book.dat
			elif [ "${dat[0]}" == "Magazine" ]
			then
				echo ${dat[0]}$'\t'${dat[1]} >> ./result/resource/magazine.dat
			elif [ "${dat[0]}" == "E-book" ]
			then
				echo ${dat[0]}$'\t'${dat[1]} >> ./result/resource/e-book.dat
			fi
		done
	fi
elif [ $1 = 'input' ]
then
	mkdir -p "./result/input"

elif [ $1 = 'space' ]
then
	mkdir -p "./result/space"
	echo $'Date[yy/mm/dd/hh]\tSpace_type\tSpace_number\tOperation\tMember_type\tMember_name\tNumber_of_member' > ./stream/space.dat
	echo $'Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name' > ./stream/input.dat
	if [ $2 = 'studyroom' ]
	then
		awk '{print}' ./space.dat | while read -a dat
		do
			if [ $3 = 'all' ]
			then

				if [ "${dat[1]}" == "StudyRoom" ]
				then
					echo ${dat[@]} >> ./stream/space.dat
				fi
			elif [ $3 -le 10 -a $3 -gt 0 ]
		done
	./lib go > ./result/space/studyroom.dat
	
	fi
elif [ $1 = 'output' ]
then
	mkdir -p "./result/output"
	if [ $2 = 'stat_table' ]
	then
		echo $'Return_code\tNumber' > ./result/output/stat_table.dat
		x=-1
		cnt=0
		while [ $x -le 16 ]
		do
			cnt=0
			while read -a dat
			do
				if [ "$x" == "${dat[1]}" ]
				then
					((cnt++))
				fi
			done < ./output.dat
			echo $x$'\t'$cnt >> ./result/output/stat_table.dat
			((x++))
		done
	fi
fi
