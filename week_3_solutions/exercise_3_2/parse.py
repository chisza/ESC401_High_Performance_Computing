#!/usr/bin/env python

import re, sys

for line in re.finditer(
            r"sum = ([0-9]*\.[0-9]+), time = ([0-9]*\.[0-9]+), threads = ([0-9]+)",
                sys.stdin.read(), re.MULTILINE):
        print("{} {}".format(line.group(2), line.group(3)))
