
# remman.c: A lightweight command line tool for remote machine management

remman.c uses ssh to transfer commands to machines. A Makefile is included for easy compilation.


## How to Compile:
  
    make

## How to Run:

    ./remman "command" "user" "machine1 machine2..."

    EXAMPLE:
    
    ./remman "ls -la" "myuser123" "13.12.123.12 122.14.12.1 123.14.123.1"


IMPORTANT: remman.c will not work unless you already have authorized ssh keys on the machines you
attmept to connect to. 

# In Progress:
Easy File Transfering
More Complex Command Line Argument Parsing

Author: Benjamin Sheth
All rights reserved.
