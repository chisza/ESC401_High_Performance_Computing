#!/bin/python3
import re
import fileinput
from pathlib import Path
import sys

pattern = re.compile(r"Computed in ([0-9]*\.[0-9]*), with N = ([0-9]*)")

f = open(sys.argv[1], "r")
contents = f.read()
f.close()

for line in contents:
    match = pattern.match(line)
    if match:
        printf("{match.group(1)} {match.group(2)}")

print("This is the end")

