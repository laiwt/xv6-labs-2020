#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

char* getline(int fd) {
    static char str[MAXARG];
    char* p = str;
    while (1) {
        if (read(fd, p, sizeof(char)) <= 0) {
            return 0;
        }
        if (*p == '\n') {
            break;
        }
        ++p;
    }
    *p = 0;
    return str;
}

int main(int argc, char *argv[]) {
    char* args[MAXARG];
    for (int i = 0; i < argc - 1; ++i) {
        args[i] = argv[i + 1];
    }
    args[argc] = 0;
    while (1) {
        char* str = getline(0);
        if (str == 0) {
            break;
        }
        int pid = fork();
        if (pid == 0) {
            args[argc - 1] = str;
            exec(args[0], args);
            fprintf(2, "Error\n");
            exit(1);
        }
        else {
            wait(0);
        }
    }
    exit(0);
}
