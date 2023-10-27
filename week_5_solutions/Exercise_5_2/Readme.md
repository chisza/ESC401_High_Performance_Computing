File permissions for ```$HOME``` -> checked with ```ls -ld $HOME``` -> ```drwx------``` -> read, write, execute for owner only

File permissions for ```$SCRATCH``` -> check with ```ls -ld $SCRATCH``` -> ```drwxr-x---+``` -> read, write, execute for owner, read and execute permissions also for the group; the plus at the end is the ACL flag (Access Control Lists), means the owner can give permissions for the file to others in the group or users

I cannot access another user's ```$HOME``` directory because based on the permissions of my ```$HOME``` directory, I wouldn't have the read permission, which would be necessary to see another user's ```$HOME``` directory.  
I could access another user's ```$SCRATCH``` directory because based on the permissions of my ```$SCRATCH``` directory, I would have read and execution permissions as long as the ```$SCRATCH``` directory belongs to another member of my group.

A new file created in my ```$HOME``` directory starts out with ```-rw-r--r--```, on ```$SCRATCH``` with ```-rw-r-----+```.  

File permissions of ```/users/jbucko``` -> checked with ```ls -ld /users/jbucko/``` -> permission: ```drwxr-----+```   
The group has reading permissions, so if there was a file ```/users/jbucko/hpc_exam_solution.txt```, it would be readable for me, but I wouldn't be able to write to it.

Command, so only the owner has full access to a directory: ```chmod 700```  
Command, that a file on ```$SCRATCH``` can be read and written to by other group members: ```chmod 760```  

File with ```000``` permissions can be overwriten with ```vim```, when the command ```:wq!``` is used to write to the file. The ```000``` can be overwriten again, e.g. with ```chmod 700```, and then the file is readable and writable again.
