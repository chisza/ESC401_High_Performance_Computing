#!/bin/bash

# 1 -> end with 00
echo "end with 00"
egrep "00$" $1

echo "start and end with 1"
egrep "^1.*1$" $1

echo "contains the pattern 110"
egrep "(110)" $1

echo "contains at least three times a 1"
egrep "1*1*1" $1

echo "contains at least three consecutive 1s"
egrep "1{3}" $1
