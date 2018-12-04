#!/bin/bash
one=`expr $1`
two=`expr $3`
thr=`expr $5`
if [ $4 = 'x' ]
then
	num=`expr $two \* $thr`
	if [ $2 = '/' ]
	then
		sum=`expr $one / $num`
	elif [ $2 = '+' ]
	then
		sum=`expr $one + $num`
	elif [ $2 = '-' ]
	then
		sum=`expr $one - $num`
	fi
elif [ $4 = '/' ]
then
	num=`expr $two / $thr`
	if [ $2 = '/' ]
	then
		sum=`expr $one / $num`
	elif [ $2 = '+' ]
	then
		sum=`expr $one + $num`
	elif [ $2 = '-' ]
	then
		sum=`expr $one - $num`
	fi
else
	if [ $2 = 'x' ]
	then
		num=`expr $one \* $two`
	elif [ $2 = '/' ]
	then
		num=`expr $one / $two`
	elif [ $2 = '+' ]
	then
		num=`expr $one + $two`
	elif [ $2 = '-' ]
	then
		num=`expr $one - $two`
	fi
	if [ $4 = 'x' ]
	then
		sum=`expr $num \* $thr`
	elif [ $4 = '/' ]
	then
		sum=`expr $num / $thr`
	elif [ $4 = '+' ]
	then
		sum=`expr $num + $thr`
	elif [ $4 = '-' ]
	then
		sum=`expr $num - $thr`
	fi
fi
echo "$1 $2 $3 $4 $5 = $sum"
