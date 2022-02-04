// lightweight C remote machine manager
// @author Benjamin Sheth
// All rights reserved, unless otherwise stated

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A method that builds and sends a command via ssh
 *
 * @param machine the ip address of the machine that will execute the command
 * @param cmd the command that will be executed
 * @user user the user to login as
 */
int sendCmd(char machine[], char cmd[], char user[]) 
{
	// building the command to be executed	
	char full_cmd[200] = "ssh ";
	strcat(full_cmd, user);
	strcat(full_cmd, "@");
	strcat(full_cmd, machine);
	strcat(full_cmd, " ");
	strcat(full_cmd, "\"");
	strcat(full_cmd, cmd);
	strcat(full_cmd, "\"");

	// executing the command	
	system(full_cmd);
	return 0;
}

// The driver for remman
// TODO: Add more complex command line argument parsing
// TODO: Add option for easily transfering files to machines
int main(int argc, char* argv[]) 
{
	// checking the number of command line arguments
	if (argc != 4) 
	{
		printf("Proper usage:\n$./remman \"command\" \"user\" \"machine1 machine2...\"\n");
		printf("Example:\n$./remman \"ls -la\" \"myusername123\" \"12.312.31.123 1.123.32.123\"\n");
		return 0;
	}

	// parsing arguments
	char* machine = strtok(argv[3], " ");
	while (machine != NULL)
	{
		sendCmd(machine, argv[1], argv[2]);
		machine = strtok(NULL, " ");
	}

	return 0;
}
