#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BLOCK 512
int main(int argc, char **argv) {
    char data[BLOCK];
    int sz;
    while (sz = read(STDIN_FILENO, data, sizeof(data)) > 0) {
        printf("Server reads : %s\n", data);
    }
    printf("File is empty\n");
    _exit(0);
}
