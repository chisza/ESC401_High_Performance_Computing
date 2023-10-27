#!/bin/bash
RE="Temperature: ([0-9]*\.[0-9]*) deg at time: ([0-9]*\.[0-9]*) sec"
count=0
sum=0
while read A; do
	if [[ "$A" =~ $RE ]] ; then
		echo "${BASH_REMATCH[1]}"
		echo "${BASH_REMATCH[2]}"
		temp=${BATCH_REMATCH[1]}
		count=$((count+1))
		sum=$((sum + temp))

	fi
done
echo "${count}"
echo "${sum}
average=$(echo "scale=2;${sum}/${count}" | bc)
echo "Average temperature: ${average}"
