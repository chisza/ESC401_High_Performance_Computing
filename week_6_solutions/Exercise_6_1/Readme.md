When parallelizing the second for loop exactly like the first loop -> get race condition -> running on different amount of
threads gives different number of 0s, but never the correct number -> resolve by reduction directive
