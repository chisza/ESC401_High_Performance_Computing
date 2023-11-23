Step-by-step guide on how to set up a VM on ScienceCloud and how to run the Poisson 
solver on it (a PDF with the screen shots of the process is in [Exercise_9_2](Exercise_9_2)

1. On ScienceCloud, under the tab Access & Security in the register Key Pair, add 
the _public key_ of the computer you work on
2. Under the tab Instances, press Launch Instance; give it a name, choose a source (Ubuntu 22.04),
add flavor (8cpu-32ram-hpcv3), make sure the key is added. Then, launch the instance.
3. After the instance spawned, it can be accessed via the terminal. For that, connect with the 
VPN, and then use the command `ssh -i .ssh/id_rsa ubuntu@172.23.53.198` (checking the ssh key
and the numbers are the IP address of the instance)
4. install the necessary packages:  
`sudo apt update`  
`sudo apt-get install cowsay`
5. test that the VM works fine with `cowsay hello there`
6. to run the Poisson solver, clone the GitHub repository into the VM
7. load the packages needed to run the files with `sudo apt install g++ make cmake`
8. to be able to plot, install python3-pip and Python packages  
`sudo apt install -q python3-pip`  
`pip3 install numpy`  
`pip3 install tk`  
`sudo apt install -q python-tk`  
9. check which Python command is Python3: `python -V`
10. run the Poisson solver: `make all` `./main`
11. get the plot with `python plot.py` in the output directory
12. to run the MPI version: install the necessary packages  
`sudo apt-get install openmpi-bin`  
`sudo apt-get install libopenmpi-dev`  
13. in the Makefile, change the compiler to `mpiCC`
14. run `make all`
15. run `mpirun -4 main` for the executable
16. close the connection to the VM in the terminal
17. on the ScienceCloud website, in the tab Instances, use create snapshot to save a snapshot of the instace
18. Delete the VM
19. The snap shot can be used to create a VM again to continue working
