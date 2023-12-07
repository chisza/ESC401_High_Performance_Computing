import re
import numpy as np
import matplotlib.pyplot as plt

# Read data from file
with open("slurm-50368862.out", "r") as file:
    lines = file.readlines()

# Define the pattern
pattern = re.compile("PI = ([\d.]+) computed in ([\d.]+) seconds, on NUM_BLOCK: (\d+), NUM_THREAD: (\d+)")

# Extract data from lines
data = []
for line in lines:
    match = pattern.match(line)
    if match:
        data.append(list(map(float, match.groups())))

# Convert data to a numpy array
parsed_data = np.array(data)

# Extract columns
seconds = parsed_data[:, 1]
num_block = parsed_data[:, 2]
num_thread = parsed_data[:, 3]

# Create the imshow plot
plt.imshow(seconds.reshape(-1, len(np.unique(num_block))),
           extent=(min(np.unique(num_block)), max(np.unique(num_block)),
                   min(np.unique(num_thread)), max(np.unique(num_thread))),
           aspect='auto', cmap='plasma', origin='lower')

# Add labels and colorbar
plt.xlabel('NUM_BLOCK')
plt.ylabel('NUM_THREAD')
plt.title('Block and Thread Dependency')
plt.colorbar(label='Seconds')

# Show the plot
plt.savefig("block_and_thread_dependency")
plt.show()