#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        puts("Usage: ./client <file> <message blocks>");
        return 1;
    };
    int i = 2;
    int fd = open(argv[1], O_WRONLY);
    while (1) {
        sleep(2);
        if (flock(fd, LOCK_EX) != 0) {
            printf("Client %d can't: access the file", getpid());
            continue;
        };
        if (i == argc) i = 2;
        char data[512];
        lseek(fd, 0, SEEK_END);
        int sz = write(fd, argv[i], strlen(argv[i]));
        if (sz > 0) printf("Client %d writes: %s\n", getpid(), argv[i]);
        flock(fd, LOCK_UN);
        i++;
    }
    close(fd);
    return 0;
}

