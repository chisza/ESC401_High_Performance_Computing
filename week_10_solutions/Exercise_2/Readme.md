The changed python code to run on python3: [mapper.py](mapper.py) and [reducer.py](reducer.py)

Answers:
* Number of map operations: 7
* Number of reduction operations: 1
* Number of treated lines: 35371
* Number of treated entries: 538568
* Created output folders / files:
  * Created folder: `output` (`output_new` for the second run, the file names change accordingly)
  * Created files:
    * `output/_SUCCESS`
    * [`output/part-00000`](part-00000)
* For the API: on localhost:9870 are the output files under Utilities -> Browse Directory -> user -> ubuntu -> output


Notes:
* to enter the created hadoop VM, add to the `.ssh` file the following:
`Host hadoop Hostname <VM instance IP address>`  
`User ubuntu`   
`ForwardX11 yes`   
`ForwardX11Trusted yes`   
`ForwardAgent yes`   
`LocalForward 9870 localhost:9870`   
`LocalForward 9864 localhost:9864`   
`LocalForward 8088 localhost:8088`  
`LocalForward 8042 localhost:8042`
* connect to VM with `ssh hadoop`
* to start the distributed file system run:  
`start-dfs.sh`  
`start-yarn.sh`  
* to see that it runs, go to `http://localhost:8088/cluster`
* create a new directory with `hadoop fs -mkdir DonaldTrump`
* move the .csv files into the directory with `hadoop fs -put trump_tweets_0?.csv /DonaldTrump`
* run `./pymapred.sh` to perform the Map & Reduction procedure
* [map_and_reduce_operations.txt](map_and_reduce_operation.txt) contains the output, that is printed to the terminal
* [part-00000](part-00000) contains the counted words
* the snap shot of the VM is `chiara_hadoop`
