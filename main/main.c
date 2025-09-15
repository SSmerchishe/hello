#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys.h"

int main(int argc, char *argv[])
{
	int res = 0;

	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			Keys key = get_key(argv[i]);
			switch (key) {
			case KEY_HELP:
				print_help();
				break;
			case KEY_VERSION:
				print_version();
				break;
			case KEY_GIT_HASH:
				print_githash();
				break;
			default:
				print_default_msg();
				res = 1;
			}
		}

		return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
	}

	printf("hello!\n");

	return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
