#include <stdio.h>
#include "options.h"
#include "help.h"

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

	return 0;
}

