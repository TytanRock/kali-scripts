#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include "help.h"
#include "revshells.h"
#include "global.h"

int main(int argc, char **args) {
	int parseReturn = parse_arguments(argc, args);
	if(parseReturn == -1) {
		printf("%s\n", helpString);
		return 0;
	}
	if(parseReturn == -2) {
		fprintf(stderr, "Only one revshell target selectable at a time\n");
		return -1;
	}
	if(parseReturn != 0) {
		fprintf(stderr, "Some error occurred when parsing: %d\n", parseReturn);
		return -1;
	}

	char *revShell = generateShellCode();
	
	/* Print out the reverse shell to the user to verify */
	printf("Reverse Shell Code: %s\n", revShell);
	/* If the clip option was set, copy the shell code to the clipboard */
	if(_global.clip) {
		/* Build the command using stack string */
		char tmp[100];
		sprintf(tmp, "/bin/echo -n \"%s\" | xclip -selection clipboard", revShell);
		/* We'll use system since it's easy */
		system(tmp);
		printf("Copied code to clipboard\n");
	}
	/* No longer need the revShell code, so let's free it */
	free(revShell);

	return 0;
}

