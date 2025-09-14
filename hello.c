#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    KEY_UNKNOW,
    KEY_HELP,
    KEY_VERSION,
    KEY_GIT_HASH
} Keys;

Keys get_key(const char *key) {
    if (strcmp(key, "--help")    == 0) return KEY_HELP;
    if (strcmp(key, "--version") == 0) return KEY_VERSION;
    if (strcmp(key, "--githash") == 0) return KEY_GIT_HASH;
    
    return KEY_UNKNOW;
}

int main(int argc, char *argv[])
{
	int res = 0;

	if (argc > 1) {
        for(int i = 1; i < argc; i++) {
            Keys key = get_key(argv[i]);

            switch (key)
            {
            case KEY_HELP:
                printf("Created by SSmerchishe.        \
                        \nAvailable keys:              \
                            \n\t--help\t\t- Help;      \
                            \n\t--version\t- Version.  \
                            \n\t--githash\t- Git Hash. \n");
                break;
            case KEY_VERSION:
                printf("Version: %s\n", PROJECT_VERSION);
                break;
            case KEY_GIT_HASH:
                printf("Git Hash: %s\n", GIT_HASH);
                break;
            default:
                printf("Input --help for help.\n");
            }
        }

        return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    }

	printf("hello\n");

	return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
