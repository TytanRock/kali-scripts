#include "stdio.h"
#include "help.h"

int main(int argc, char **args) {
	/* There must be at least 1 argument */
	if(argc <= 1) {
		printf("%s\n", helpString);
	}

	return 0;
}

