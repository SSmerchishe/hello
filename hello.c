#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--version") == 0) {
        printf("%s\n", PROJECT_VERSION);
        return 0;
    }
    printf("hello\n");
    return 0;
}

