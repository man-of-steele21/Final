#!/bin/bash

i=0
START=$(date +%s)
END=$(echo "$START+100" | bc)
finished=0

    for (( c=1; finished!=1; c++ ))
    do
	x=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	y=`awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}'`
	z=$(echo "sqrt($x*$x+$y*$y)" | bc)
	if (( $(echo "$z<1" | bc -l) )); then
	    i=$((i+1))
	fi
	CURRENTTIME=$(date +%s)
	if (( $(echo "$CURRENTTIME>$END" | bc) )); then
	    finished=1
	fi
    done

echo "Number of points ran: $c"

res=$(echo "4*$i/$c" | bc -l)

pi=$(echo "scale=10; 4*a(1)" | bc -l)

if (( $(echo "$res<$pi" | bc -l) )); then
	dev=$(echo "$pi-$res" | bc -l)
else
    dev=$(echo "$res-$pi" | bc -l)
fi

err=$(echo "$dev/$pi*100" | bc -l)

printf "Result: %.5f\n" $res

printf "Deviation: %.5f\n" $dev

printf "Percent error: %.5f percent\n" $err
