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

void print_help()
{
	printf(APP_HELP);
}
void print_version()
{
	printf("Version: %s", PROJECT_VERSION);
}
void print_githash()
{
	printf("GIT HASH: %s", GIT_HASH);
}
void print_default_msg()
{
	printf("Input --help for help.\n");
}