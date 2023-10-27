#!/bin/python3
import re
import fileinput
from pathlib import Path

pattern = re.compile(r"Temperature: ([0-9]*\.[0-9]*) deg at time: ([0-9]*\.[0-9]*) sec")

print("TEMPERATURE TIME")

count = 0
sum = 0

for idx, file_name in enumerate(Path(".").glob("*.txt")):
	with open(file_name) as f_obj:
		for line in f_obj:
			match = pattern.match(line)
			if match:
				print(f"{match.group(1)} {match.group(2)}")
				count += 1
				sum += float(match.group(1))

average = sum/count
print(f"Average temperature: {average}")



