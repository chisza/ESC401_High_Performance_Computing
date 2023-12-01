# get the image
FROM ubuntu:latest

# make sure I have not to enter a geographic range
ENV DEBIAN_FRONTEND=noninteractive

# get the packages
RUN apt-get update -q &&\
	apt-get install -y -q\
	make cmake build-essential python3 python3-dev python3-pip python-tk

RUN pip3 install matplotlib
RUN pip3 install tk
RUN pip3 install numpy

# copy the file into the directory poisson
COPY . /poisson

# change work directory to poisson
WORKDIR /poisson

# compile the files
RUN make all

# run the executable
CMD ./main
