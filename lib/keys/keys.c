#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys.h"

Keys get_key(const char *key)
{
	if (strcmp(key, "--help") == 0)
		return KEY_HELP;
	if (strcmp(key, "--version") == 0)
		return KEY_VERSION;
	if (strcmp(key, "--githash") == 0)
		return KEY_GIT_HASH;

	return KEY_UNKNOW;
}

int keys_headler(int argc, char *argv[])
{
	int res = 0;

	for (int i = 1; i < argc; i++) {
		Keys key = get_key(argv[i]);
		switch (key) {
		case KEY_HELP:
			printf(APP_HELP);
			break;
		case KEY_VERSION:
			printf("Version: %s\n", PROJECT_VERSION);
			break;
		case KEY_GIT_HASH:
			printf("GIT HASH: %s\n", GIT_HASH);
			break;
		default:
			printf("Input --help for help.\n");
			res = 1;
		}
	}
	return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}