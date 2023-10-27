File permissions for ```$HOME``` -> checked with ```ls -ld $HOME``` -> ```drwx------``` -> read, write, execute for owner only

File permissions for ```$SCRATCH``` -> check with ```ls -ld $SCRATCH``` -> ```drwxr-x---+``` -> read, write, execute for owner, read and execute permissions also for the group; the plus at the end is the ACL flag (Access Control Lists), means the owner can give permissions for the file to others in the group

I cannot access another user's ```$HOME``` directory because based on the permissions of my ```$HOME``` directory, I wouldn't have the read permission, which would be necessary to see another user's ```$HOME``` directory.  
I could access another user's ```$SCRATCH``` directory because based on the permissions of my ```$SCRATCH``` directory, I would have read and execution permissions as long as the ```$SCRATCH``` directory belongs to another member of my group.

A new file created 
