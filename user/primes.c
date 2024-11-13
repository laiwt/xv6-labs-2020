#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int from_left(int fd) {
    int buf = 0;
    read(fd, &buf, sizeof(int));
    return buf;
}

void to_right(int fd, int x) {
    write(fd, &x, sizeof(int));
}

void func(int left) {
    int x = from_left(left);
    if (x == 0) {
        exit(0);
    }
    printf("prime %d\n", x);
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0) {
        close(fd[1]);
        func(fd[0]);
    }
    else {
        close(fd[0]);
        while (1) {
            int num = from_left(left);
            if (num == 0) {
                break;
            }
            if (num % x) {
                to_right(fd[1], num);
            }
        }
        close(fd[1]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char const *argv[]) {
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0) {
        close(fd[1]);
        func(fd[0]);
    }
    else {
        close(fd[0]);
        for (int i = 2; i <= 35; ++i) {
            write(fd[1], &i, sizeof(int));
        }
        close(fd[1]);
        wait(0);
    }
    exit(0);
}
