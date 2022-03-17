#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK 512
int main(int argc, char **argv) {
    if (argc < 1) {
        printf("USAGE: ./client <message>\n");
        _exit(1);
    }
    int fd_write = open("./tmp/data", O_WRONLY);
    char data[BLOCK];
    int sz;
    for (int i = 1; i < argc; i++) {
        sprintf(data, "PID: %d, Data: %s", getpid(), argv[i]);
        sz = write(fd_write, data, sizeof(data));
    }
    close(fd_write);
    _exit(0);
}
