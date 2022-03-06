#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK 512
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("USAGE: ./server <pipefd_read>\n");
        _exit(1);
    }
    int pipefd_read = strtol(argv[1], NULL, 10);
    printf("%d", pipefd_read);
    char data[BLOCK];
    int sz;
    while (sz = read(pipefd_read, data, sizeof(data)) > 0)
        printf("Server reads : %s\n", data);
    printf("File is empty\n");
    _exit(0);
}