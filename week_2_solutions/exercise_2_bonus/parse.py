#import modules
import os

# get current directory
directory = os.getcwd()

# iterate through the files and get the number of threads and the time
for filename in os.listdir(directory):
    if filename.endswith(".out"):
        myfile = open(filename, "r")
        lines = myfile.readlines()

        # threads
        mythreads = 0
        for line in lines:
            if line.startswith("Thread"):
                rank = int(line.split(" ")[2])

                if rank > mythreads:
                    mythreads = rank
                else:
                    continue

            elif line.startswith("Computed"):
                time = float(line.split(" ")[2])

            else:
                continue

        print(f"{time}, {rank + 1}")
