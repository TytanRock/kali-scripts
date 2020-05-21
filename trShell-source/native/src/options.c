#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "global.h"
#include "options.h"

#define DEFAULT_LADAPTER "tun0"

/* These are the available long options for this program */
char clipOpt[] = "clip";
char targetOpt[] = "target";
char lhostOpt[] = "lhost";
char ladapterOpt[] = "ladapter";
char portOpt[] = "port";
char netcatOpt[] = "netcat";
char bashOpt[] = "bash";

/* These are the available short options for this program */
char validOpts[] = "ct:h:a:p:nb";

/* These are the returns of the options for this program */
enum options {
        clip = 'c',
        target = 't',
        lhost = 'h',
        ladapter = 'a',
	port = 'p',
        netcat = 'n',
        bash = 'b',
};

/* Array of longoptions that are available */
struct option longOptions[] = {
	/* Format of longoption struct defined in man page of getopt */
        {                                                                                                          
                .name = clipOpt, // Name of option
                .has_arg = 0, // Does option require argument?
		.flag = NULL, // This will always be NULL for this program
                .val = clip, // Value getopts_long will return, matches our validOpts string
        },                                                                                                         
        {                                                                                                          
                .name = targetOpt,                                                                                 
                .has_arg = 1, 
                .flag = NULL,                                                                                      
                .val = target,                                                                                     
        },                                                                                                         
        {                                                                                                          
                .name = lhostOpt,                                                                                  
                .has_arg = 1,                                                                                      
                .flag = NULL,                                                                                      
                .val = lhost,                                                                                      
        },                                                                                                         
        {                                                                                                          
                .name = ladapterOpt,                                                                               
                .has_arg = 1,                                                                                      
                .flag = NULL,                                                                                      
                .val = ladapter,                                                                                   
        },         
	{
		.name = portOpt,
		.has_arg = 1,
		.flag = NULL,
		.val = port,
	},	
        {                                                                                                          
                .name = netcatOpt,                                                                                 
                .has_arg = 0,                                                                                      
                .flag = NULL,                                                                                      
                .val = netcat,                                                                                     
        },                                                                                                         
        {                                                                                                          
                .name = bashOpt,
                .has_arg = 0,
                .flag = NULL,
                .val = bash,
        },

	/* last struct member must be filled with zeros */
	{
		.name = NULL,
		.has_arg = 0,
		.flag = NULL,
		.val = 0,
	}
};

/* Parse arguments and set our global variables */
int parse_arguments(int argc, char **args) {
	enum options selectedOption;
	int targetSelected = 0; // Ensure multiple targets are not selected
	
	/* Initialize global variables */
	_global.target = NULL;
	_global.lhost = NULL;
	_global.ladapter = NULL;
	_global.port = 7762;
	_global.revTarget = target_Unknown;
	_global.clip = 0;

	while ((selectedOption = getopt_long(argc, args, validOpts, longOptions, NULL)) != -1) {
		switch(selectedOption) {
			case clip:
				_global.clip = 1;
				break;
			case target:
				_global.target = calloc(sizeof(char), strlen(optarg));
				strcpy(_global.target, optarg);
				break;
			case lhost:
				_global.lhost = calloc(sizeof(char), strlen(optarg));
				strcpy(_global.lhost, optarg);
				break;
			case ladapter:
				_global.ladapter = calloc(sizeof(char), strlen(optarg));
				strcpy(_global.ladapter, optarg);
				break;
			case port:
				_global.port = atoi(optarg);
				break;
			case netcat:
				if(targetSelected <= 2) ++targetSelected;
				_global.revTarget = target_Netcat;
				break;
			case bash:
				if(targetSelected <= 2) ++targetSelected;
				_global.revTarget = target_Bash;
				break;
		}
	}
	
	/* No target selected/unknown :w
	 * target selected */
	if(targetSelected == 0 || _global.revTarget == target_Unknown) return -1;
	/* Too mmany targets selected */
	if(targetSelected != 1) return -2;
	
	/* At this point, we know we have what we need, let's take care all necessary globals */
	/* First, if lhost is null, that means we need to find lhost from ladapter */
	if(_global.lhost == NULL) {
		/* If our adapter is not set, use default (tun0) */
		if(_global.ladapter == NULL) {
			_global.ladapter = calloc(sizeof(char), strlen(DEFAULT_LADAPTER));
			strcpy(_global.ladapter, DEFAULT_LADAPTER);
		}
		/* Call system command to get ip address of adapter */
		/* Fun with pipes and forks! */
		int pipefd[2]; // Our two pipe file descriptors
		if(pipe(pipefd) < 0) {
			/* Our pipe failed!?! */
			return -3;
		}
		int pid = fork();
		if(pid < 0) {
			/* Our fork failed!?! */
			return -4;
		}
		if(pid == 0) {
			/* This is the child, configure stdout */
			close(pipefd[0]); // This is used by parent
			dup2(pipefd[1], STDOUT_FILENO); // Duplicate stdout to pipe[1]
			close(pipefd[1]); // Close pipe[1] now that we've configured it
			
			char command[100];
			/* Form our command */
			sprintf(command, 
				"ip -4 addr show %s | grep inet | awk '{print $2}'",
				_global.ladapter);
			/* Execute it, this replaces our current image */
			execl("/bin/sh", "sh", "-c", command, NULL);
			/* We should never make it here */
			exit(-5);
		}
		/* This is parent */
		close(pipefd[1]);
		int ret;
		waitpid(pid, &ret, 0);
		ret = WEXITSTATUS(ret);
		if(ret != 0) return -5;
		char ip[20];
		read(pipefd[0], ip, sizeof(ip));
		close(pipefd[0]);

		/* Sterilize IP string to remove newline */
		ip[(int)(strchr(ip, '/') - ip)] = '\0';

		/* We have our IP, let's set it globally */
		_global.lhost = calloc(sizeof(char), strlen(ip));
		strcpy(_global.lhost, ip);
	}

	return 0;
}

