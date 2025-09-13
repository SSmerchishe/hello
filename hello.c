#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void key_output(int count_argc, char **argv, char *key, char *print_message) {
    if (strcmp(argv[1], key) == 0) {
        printf("%s\n", print_message);
    }
}

int main(int argc, char *argv[]) {
    int res = 0;
    if (argc > 1) {
        key_output(argc, argv, "--version", PROJECT_VERSION);
        key_output(argc, argv, "--githash", GIT_HASH);
        key_output(argc, argv, "--help", "Created by SSmerchishe.\
            \nAvailable keys:\n\t--help - Help;\
            \n\t--version - Version.\
            \n\t--githash - Git Hash.\n");
        return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    printf("hello\n");
    return res == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

