// lightweight C remote machine manager
// @author Benjamin Sheth
// All rights reserved, unless otherwise stated

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MACHINE_LEN 50
#define STD_LEN 200
#define BUF_LEN 1024

/**
 * @brief sends a command to a remote machine to be executed
 * 
 * @param machine the hostname of the machine that will execute the command
 * @param cmd the command that will be executed
 * @param user the user to login as
 * @return int 
 */
int sendCmd(char* user, char* machine, char* cmd) {
	// building the command to be executed	
	char full_cmd[BUF_LEN] = "ssh ";
	strncat(full_cmd, user, STD_LEN);
	strncat(full_cmd, "@", 2);
	strncat(full_cmd, machine, MACHINE_LEN);
	strncat(full_cmd, " ", 2);
	strncat(full_cmd, "\"", 2);
	strncat(full_cmd, cmd, STD_LEN);
	strncat(full_cmd, "\"", 2);

	// executing the command	
	system(full_cmd);
	return 0;
}

/**
 * @brief copies a file to a remote machine
 * 
 * @param machine the hostname of the machine to copy the file to
 * @param file the file to copy from the local machine
 * @param user the user to login as
 * @param location the location to copy the file to on the remote machine
 * @return int 0 on success
 */
int sendFile(char* file, char* user, char* machine, char* location) {
	char full_cmd[BUF_LEN] = "scp ";
	strncat(full_cmd, file, STD_LEN);
	strncat(full_cmd, " ", 2);
	strncat(full_cmd, user, STD_LEN);
	strncat(full_cmd, "@", 2);
	strncat(full_cmd, machine, MACHINE_LEN);
	strncat(full_cmd, ":", 2);
	strncat(full_cmd, location, STD_LEN);

	system(full_cmd);
	return 0;
}

/**
 * @brief copies a file from a remote machine
 * 
 * @param machine the machine to be copied from
 * @param file the file to be copied
 * @param user the user to login as 
 * @param location the location to put the copy on the local machine
 * @return int 0 on success
 */
int getFile(char* user, char* machine, char* file, char* location) {
	char full_cmd[BUF_LEN] = "scp ";
	strncat(full_cmd, user, STD_LEN);
	strncat(full_cmd, "@", 2);
	strncat(full_cmd, machine, MACHINE_LEN);
	strncat(full_cmd, ":", 2);
	strncat(full_cmd, file, STD_LEN);
	strncat(full_cmd, " ", 2);
	strncat(full_cmd, location, STD_LEN);

	if (location[strlen(location)-1] != '/') {
		strncat(full_cmd, "/", 2);
	}

	// getting the file name
	char* file_name = strtok(file, "/");
	char* prev;
	while (file_name != NULL){
		prev = file_name;
		file_name = strtok(NULL, "/");
	}

	// the file from the remote machine will be named in the following form:
	// "<remote hostname>_<file name>"
	strncat(full_cmd, machine, MACHINE_LEN);
	strncat(full_cmd, "_", 2);
	strncat(full_cmd, prev, STD_LEN);
}

int printExample() {
	printf("Sending command usage:\n$ ./remman s \"user\" \"machine1 machine2...\" \"command\"\n");
	printf("Example:\n$ ./remman s \"ls -la\" \"myusername123\" \"12.312.31.123 1.123.32.123\"\n");
	printf("Sending file usage:\n$ ./remman c \"file\"  \"user\" \"machine1 machine2...\" \"location\"\n");
	printf("Example:\n$ ./remman c \"file.txt\" \"myusername123\" \"12.312.31.123 1.123.32.123\" \"~/documents\"\n");
	printf("Getting file usage:\n$ ./remman g  \"user\" \"machine1 machine2...\" \"file\" \"location\"\n");
	printf("Example:\n$ ./remman g \"myusername123\" \"12.312.31.123 1.123.32.123\" \"~/myfolder/file.txt\" \"./mydir\"\n");
	return 0;
}

// The driver for remman
int main(int argc, char* argv[]) {

	// check that arguments are not empty
	for (int i = 0; i < argc; i++) {
		if (strlen(argv[i]) == 0) {
			printExample();
			exit(1);
		}
	}

	if (argc == 5) {
		// parse send command
		if (strncmp(argv[1], "s", 1)) {
			char* machine = strtok(argv[3], " ");
			while (machine != NULL) {
				sendCmd(argv[2], machine, argv[4]);
				machine = strtok(NULL, " ");
			}
		}
		else {
			printExample();
			exit(1);
		}
	}
	else if (argc == 6) {
		// parse send file
		if (strncmp(argv[1], "c", 1)) {
			char* machine = strtok(argv[4], " ");
			while (machine != NULL) {
				sendFile(argv[2], argv[3], machine, argv[5]);
				machine = strtok(NULL, " ");
			}
		}
		// parse get file
		else if (strncmp(argv[1], "g", 1)) {
			char* machine = strtok(argv[3], " ");
			while (machine != NULL) {
				getFile(argv[2], machine, argv[4], argv[5]);
				machine = strtok(NULL, " ");
			}
		}
		else {
			printExample();
			exit(1);
		}
	}
	else {
		printExample();
		exit(1);
	}

	return 0;
}
