#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys.h"

int main(int argc, char *argv[])
{
	int res = 0;

	if (!(res = keys_headler(argc, argv)) && argc == 1) {
		printf("hello!\n");
	}

	return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
