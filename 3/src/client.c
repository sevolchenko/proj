#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK 512
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("USAGE: ./client <pipefd_write> <message>\n");
        _exit(1);
    }
    char pid[BLOCK];
    int sz;
    for (int i = 1; i < argc; i++) {
        sprintf(pid, "PID: %d, Data: %s", getpid(), argv[i]);
        sz = write(STDOUT_FILENO, pid, sizeof(pid));
    }
    _exit(0);
}
