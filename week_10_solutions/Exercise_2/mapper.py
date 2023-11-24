#!/usr/bin/env python3
"""mapper.py"""

import sys
import string

trans = str.maketrans("", "", string.punctuation)

# input comes from STDIN (standard input)
for line in sys.stdin:
    # remove leading and trailing whitespace and punctuation
    line = line.strip().translate(trans).lower()

    words = line.split()
    # increase counters
    for word in words:
        # write the results to STDOUT (standard output);
        # what we output here will be the input for the
        # Reduce step, i.e. the input for reducer.py
        #
        # tab-delimited; the trivial word count is 1
        print(f"{word}\t1")
        #print '%s\t%s' % (word, 1)
