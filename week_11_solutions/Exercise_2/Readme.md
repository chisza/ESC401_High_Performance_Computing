Running the program with CUDA, shows the same pattern as as running with OpenACC, the first slower than the rest. 
Overall, CUDA faster than OpenACC. The reasoning for this I had to google, and apprently this is due to that OpenACC has to translate to object 
code, while CUDA can run it directly.
