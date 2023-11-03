#!/usr/bin/env python

import re, sys

for line in re.finditer(
        r"Computed in ([0-9]*\.[0-9]*), with N = ([0-9]*)",
        sys.stdin.read(), re.MULTILINE):
    print("{} {}".format(line.group(1), line.group(2)))
