#!/bin/bash

i=0

if [ $# -ne 1 ]; then
    echo "Script usage: Problem1.sh (number of points to be generated)"
    exit 1
else
    for (( c=1; c<=$1; c++ ))
    do
	x=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	y=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	z=$(echo "sqrt($x*$x+$y*$y)" | bc)
	if (( $(echo "$z<1" | bc -l) )); then
	    i=$((i+1))
	fi
    done
fi

res=$(echo "4*$i/$1" | bc -l)

pi=$(echo "scale=10; 4*a(1)" | bc -l)

if (( $(echo "$res<$pi" | bc -l) )); then
	dev=$(echo "$pi-$res" | bc -l)
else
    dev=$(echo "$res-$pi" | bc -l)
fi

err=$(echo "$dev/$pi*100" | bc -l)

printf "Result: %.5f\n" $res

printf "Deviation: %.5f\n" $dev

printf "Percent error: %.5fpercent\n" $err
