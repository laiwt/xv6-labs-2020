#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char const *argv[]) {
    int fd1[2], fd2[2];
    char ch = 'a';
    pipe(fd1);
    pipe(fd2);
    char buf;
    int pid = fork();
    if (pid == 0) {
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(fd2[1], &ch, 1);
    }
    else {
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1], &ch, 1);
        read(fd2[0], &buf, 1);
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}
