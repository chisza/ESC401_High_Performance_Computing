#!/bin/bash

function isprime () {
	local x=$1
	if [[ "$x" =~ ^[0-9]*$ ]] ;
	then 
		local num=$(factor $x | wc -w)
		if [[ $num -eq 2 ]] ;
		then
			return 0
		else
			return 1
		fi
	else
		echo "ERROR: The given input is not a positive integer: $num"
		exit 0
	fi	

}

start=`date +%s.%N`

while test -n "$1" ; do

	if isprime $1 ; then
		echo "$1 is prime"
	else
		echo "$1 is composite"
	fi
	shift
done

end=`date +%s.%N`
runtime=$( echo "$end - $start" | bc -l )
echo "Execution time: $runtime"
