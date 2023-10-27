#!/bin/bash

function isprime () {
	local x=$1
	local y=$2
	local z=$3
	if ([[ "$x" =~ ^[0-9]*$ ]] && [[ "$y" =~ ^[0-9]*$ ]] && [[ "$z" =~ ^[0-9]*$ ]]) ;
	then 
		for i in $(seq $x $y $z) ; do
			local num=$(factor $i | wc -w)
			if [[ $num -eq 2 ]] ;	
			then
				echo "$i is prime"
			else 
				echo "$i is composite"
			fi
		done
		return 0
	else
		echo "ERROR: The given input is not a positive integer: $num"
		exit 0
	fi
}

start=`date +%s.%N`

isprime $1 $2 $3

end=`date +%s.%N`
runtime=$( echo "$end - $start" | bc -l )
echo "Execution time: $runtime"
