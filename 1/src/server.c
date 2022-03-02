/*
 *p6.c
 * reader
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <stdlib.h>
#include <signal.h>

int main (int argc, char** argv)
{
     if (argc < 3) {
        puts("Usage: ./server <file> <w_pid>"); // sout
        return 1;
     };
     FILE* f = fopen(argv[1], "r");
     int fd = fileno(f);
     pid_t pid = getpid();
     pid_t wpid = (pid_t) strtol(argv[2], NULL, 10);
     int i;
     while (flock(fd, LOCK_EX) == 0) {
         printf("Reader flock (PID=%d) interact to %d\n ", pid, wpid);
         while (!feof(f)) {
             fscanf(f, "%d\n", &i);
             printf(" %d", i);
         }
         fflush(NULL);
         rewind(f);
         flock(fd, LOCK_UN);
         kill(wpid, SIGCONT);
         sleep(5);
     }
     fclose(f);
     return 0;
}

