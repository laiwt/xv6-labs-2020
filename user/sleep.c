#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(2, "Error\n");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}
