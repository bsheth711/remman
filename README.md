
# remman.c: A lightweight command line tool for remote machine management

remman.c uses ssh to transfer commands to machines. A Makefile is included for easy compilation.


## How to Compile:
  
    make

## How to Run:
    Sending command usage:
    $ ./remman s "user" "machine1 machine2..." "command"
    Example:
    $ ./remman s "ls -la" "myusername123" "12.312.31.123 1.123.32.123"

    Sending file usage:
    $ ./remman c "file"  "user" "machine1 machine2..." "location"
    Example:
    $ ./remman c "file.txt" "myusername123" "12.312.31.123 1.123.32.123" "~/documents"

    Getting file usage:
    $ ./remman g  "user" "machine1 machine2..." "file" "location"
    Example:
    $ ./remman g "myusername123" "12.312.31.123 1.123.32.123" "~/myfolder/file.txt" "./mydir"


IMPORTANT: remman.c will not work unless you already have authorized ssh keys on the machines you attmept to connect to. Additionally, command injection is possible--remman is meant to only be manually used. 

# In Progress:
File I/O

Author: Benjamin Sheth
All rights reserved.
