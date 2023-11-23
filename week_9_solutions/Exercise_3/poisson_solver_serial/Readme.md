Some Comments to Exercise 9.3
* adding `ENV DEBIAN_FRONTEND=noninteractive` to the [Dockerfile](Dockerfile) to avoid being asked about the geographic region
* on local machine:  
to run: `docker run poisson` (poisson is the "name" of the container I want to run)  
to get output: `docker run -v "$(pwd)"/output:/poisson/output poisson:latest` ( `$(pwd)` gets the 
path till the current location,  `/output` is the output folder the stuff go to, after the `:`, specify
where the desired output comes from from within the container, here from `/poisson/output`)
* for pushing:  
rename with `docker tag poisson:latest chiza99/poisson:latest`  
push with `docker push chiza99/poisson:latest
* on VM: everything with Docker requires `sudo`  
pull the image with `sudo docker pull chiza99/poisson:latest`  
run with `sudo docker run -v "$(pwd)"/output:/poisson/output`, make a directory `output` beforehand


The snap shot of the VM is chiara_exercise_9.

The poisson image is [here](https://hub.docker.com/r/chiza99/poisson/tags)
