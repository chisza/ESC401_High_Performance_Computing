#!/usr/bin/python
import re
import fileinput
from pathlib import Path

pattern = re.compile("Temperature: ([0-9]*\.[0-9]*) deg at time: ([0-9]*\.[0-9]*) sec")

for idx, file_name in enumerate(Path(".").glob("*.txt")):
	for line in file_name:
		match = pattern.match(line)
		if match:
			print(f"{match.group(1)} {match.group(2)}")

