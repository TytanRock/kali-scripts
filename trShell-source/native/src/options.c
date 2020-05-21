#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "global.h"
#include "options.h"

/* These are the available long options for this program */
char clipOpt[] = "clip";
char targetOpt[] = "target";
char lhostOpt[] = "lhost";
char ladapterOpt[] = "ladapter";
char netcatOpt[] = "netcat";
char bashOpt[] = "bash";

/* These are the available short options for this program */
char validOpts[] = "ct:h:a:nb";

/* These are the returns of the options for this program */
enum options {
        clip = 'c',
        target = 't',
        lhost = 'h',
        ladapter = 'a',
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
	
	if(targetSelected == 0) return -1;
	if(targetSelected != 1) return -2;
	return 0;
}
