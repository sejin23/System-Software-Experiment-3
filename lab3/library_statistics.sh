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
	if [ $2 = 'all' ]
	then
		./library_statistics.sh input book
		./library_statistics.sh input e-book
		./library_statistics.sh input magazine
		./library_statistics.sh input undergraduate
		./library_statistics.sh input graduate
		./library_statistics.sh space faculty
	else
		echo $'Date[yy/mm/dd/hh]\tSpace_type\tSpace_number\tOperation\tMember_type\tMember_name\tNumber_of_member' > ./stream/space.dat
		echo $'Date[yy/mm/dd]\tResource_type\tResource_name\tOperation\tMember_type\tMember_name' > ./stream/input.dat
		if [ $2 = 'book' ]
		then
			awk '{print}' ./input.dat | while read -a dat
			do
				if [ "${dat[1]}" == "Book" ]
				then
					echo ${dat[@]} >> ./stream/input.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/input/book.dat
		elif [ $2 = 'magazine' ]
		then
			awk '{print}' ./input.dat | while read -a dat
			do
				if [ "${dat[1]}" == "Magazine" ]
				then
					echo ${dat[@]} >> ./stream/input.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/input/magazine.dat
		elif [ $2 = 'e-book' ]
		then
			awk '{print}' ./input.dat | while read -a dat
			do
				if [ "${dat[1]}" == "E-book" ]
				then
					echo ${dat[@]} >> ./stream/input.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/input/e-book.dat
		elif [ $2 = 'undergraduate' ]
		then
			awk '{print}' ./input.dat | while read -a dat
			do
				if [ "${dat[4]}" == "Undergraduate" ]
				then
					echo ${dat[@]} >> ./stream/input.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/input/undergraduate.dat
		elif [ $2 = 'graduate' ]
		then
			awk '{print}' ./input.dat | while read -a dat
			do
				if [ "${dat[4]}" == "Graduate" ]
				then
					echo ${dat[@]} >> ./stream/input.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/input/graduate.dat
		elif [ $2 = 'faculty' ]
		then
			awk '{print}' ./input.dat | while read -a dat
			do
				if [ "${dat[4]}" == "Faculty" ]
				then
					echo ${dat[@]} >> ./stream/input.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/input/faculty.dat
		elif [ $2 = 'date' ]
		then
			awk '{print}' ./input.dat | while read -a dat
			do
				if [ "${dat[0]}" != "Date[yy/mm/dd]" ]
				then
					year=`echo ${dat[0]} | cut -d "/" -f1`
					month=`echo ${dat[0]} | cut -d "/" -f2`
					day=`echo ${dat[0]} | cut -d "/" -f3`
					fromy=`echo $3 | cut -d "/" -f1`
					fromm=`echo $3 | cut -d "/" -f2`
					fromd=`echo $3 | cut -d "/" -f3`
					toy=`echo $4 | cut -d "/" -f1`
					tom=`echo $4 | cut -d "/" -f2`
					tod=`echo $4 | cut -d "/" -f3`
					time=`expr $year \* 360 + $month \* 30 + $day`
					fromt=`expr $fromy \* 360 + $fromm \* 30 + $fromd`
					tot=`expr $toy \* 360 + $tom \* 30 + $tod`
					if [ $time -ge $fromt -a $time -le $tot ]
					then
						echo ${dat[@]} >> ./stream/input.dat
					fi
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/input/date.dat
		fi
		cp space.dat ./stream/space.dat
		cp input.dat ./stream/input.dat
	fi
elif [ $1 = 'space' ]
then
	mkdir -p "./result/space"
	if [ $2 = 'all' ]
	then
		./library_statistics.sh space studyroom all
		./library_statistics.sh space seat all
		./library_statistics.sh space undergraduate
		./library_statistics.sh space graduate
		./library_statistics.sh space faculty
	else
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
				then
					if [ "${dat[1]}" == "StudyRoom" -a "$3" == "${dat[2]}" ]
					then
						echo ${dat[@]} >> ./stream/space.dat
					fi
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/space/studyroom.dat
		elif [ $2 = 'seat' ]
		then
			awk '{print}' ./space.dat | while read -a dat
			do
				if [ $3 = 'all' ]
				then
					if [ "${dat[1]}" == "Seat" ]
					then
						echo ${dat[@]} >> ./stream/space.dat
					fi
				elif [ $3 -le 3 -a $3 -gt 0 ]
				then
					if [ "${dat[1]}" == "Seat" -a "$3" == "${dat[2]}" ]
					then
						echo ${dat[@]} >> ./stream/space.dat
					fi
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/space/seat.dat
		elif [ $2 = 'undergraduate' ]
		then
			awk '{print}' ./space.dat | while read -a dat
			do
				if [ "${dat[4]}" == "Undergraduate" ]
				then
					echo ${dat[@]} >> ./stream/space.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/space/undergraduate.dat
		elif [ $2 = 'graduate' ]
		then
			awk '{print}' ./space.dat | while read -a dat
			do
				if [ "${dat[4]}" == "Graduate" ]
				then
					echo ${dat[@]} >> ./stream/space.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/space/graduate.dat
		elif [ $2 = 'faculty' ]
		then
			awk '{print}' ./space.dat | while read -a dat
			do
				if [ "${dat[4]}" == "Faculty" ]
				then
					echo ${dat[@]} >> ./stream/space.dat
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/space/faculty.dat
		elif [ $2 = 'date' ]
		then
			awk '{print}' ./space.dat | while read -a dat
			do
				if [ "${dat[0]}" != "Date[yy/mm/dd/hh]" ]
				then
					year=`echo ${dat[0]} | cut -d "/" -f1`
					month=`echo ${dat[0]} | cut -d "/" -f2`
					day=`echo ${dat[0]} | cut -d "/" -f3`
					hour=`echo ${dat[0]} | cut -d "/" -f4`
					fromy=`echo $3 | cut -d "/" -f1`
					fromm=`echo $3 | cut -d "/" -f2`
					fromd=`echo $3 | cut -d "/" -f3`
					fromh=`echo $3 | cut -d "/" -f4`
					toy=`echo $4 | cut -d "/" -f1`
					tom=`echo $4 | cut -d "/" -f2`
					tod=`echo $4 | cut -d "/" -f3`
					toh=`echo $4 | cut -d "/" -f4`
					time=`expr $year \* 8640 + $month \* 720 + $day \* 24 + $hour`
					fromt=`expr $fromy \* 8640 + $fromm \* 720 + $fromd \* 24 + $fromh`
					tot=`expr $toy \* 8640 + $tom \* 720 + $tod \* 24 + $toh`
					if [ $time -ge $fromt -a $time -le $tot ]
					then
						echo ${dat[@]} >> ./stream/space.dat
					fi
				fi
			done
			./lib go
			cp ./stream/output.dat ./result/space/date.dat
		fi
		cp space.dat ./stream/space.dat
		cp input.dat ./stream/input.dat
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
