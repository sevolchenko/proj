#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv)
{
     if (argc != 2) {
        puts("Usage: ./server <file>"); // sout
        return 1;
     };
     int fd = open(argv[1], O_RDONLY);
     while (1) {
         if (flock(fd, LOCK_EX) != 0) {
              printf("Server %d can't: access the file", getpid());
              continue;
         }
         char data[512];
         ssize_t size = read(fd, data, sizeof(data));
         if (size > 0) {
             char word[size];
             strncpy(word, data, size);
             word[size] = 0;
             printf("Server %d reads: %s\n", getpid(), word);
         }
         flock(fd, LOCK_UN);
     }
     close(fd);
     return 0;
}