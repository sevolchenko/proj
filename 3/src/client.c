#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    if (argc < 3) {
        printf("USAGE: ./client <pipefd_write> <message>\n");
        _exit(1);
    }
    int pipefd_write = strtol(argv[2], NULL, 10);
    int sz;
    for (int i=1; i<argc; i++)
        sz = write(pipefd_write, argv[i], sizeof(argv[i]));
    _exit(0);
}