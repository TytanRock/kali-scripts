#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "global.h"
#include "shellWrapper.h"

void startWrapper() {
	/* First, let's initialize the pipes */
	int pipeIn[2];
	if(pipe(pipeIn) < 0) {
		/* Our pipe failed !?! */
		exit(-10);
	}
	/* Now let's fork */
	int pid = fork();
	if(pid < 0) {
		/* Our fork failed !?! */
		exit(-10);
	}
	if(pid == 0) {
		/* This is the child, let's configure pipes */
		close(pipeIn[1]); // Not using pipeIn's input
		dup2(pipeIn[0], STDIN_FILENO); // Piping into stdin
		close(pipeIn[0]); // Not using stdin anymore

		char tmp[100];
		sprintf(tmp, "netcat -lnvp %d", _global.port);
		execl("/bin/sh", "sh", "-c", tmp, NULL);
		/* Should never get here */
		exit(-10);
	}
	close(pipeIn[0]); // Not using pipeIn's output
	/* We are actually reading STDIN and skimming it for special commands */

	char *command;
	size_t commandSize = 100;
	command = malloc(commandSize);
	while(1) {
		size_t size = getline(&command, &commandSize, stdin);

		if(strstr(command, "tr") == command) {
			printf("To be handled\n");
		} else {
			write(pipeIn[1], command, size);
		}
	}
}

