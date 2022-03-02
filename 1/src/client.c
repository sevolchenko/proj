/*
 *p5.c
 * writer
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <signal.h>
void sig_handler(int sig)
{
    if (sig == SIGCONT)
        printf("..continue writer\n");
}

int main(int argc, char** argv)
{
    if (argc == 1) {
        puts("Usage: ./client <file>");
        return 1;
    };
    if (signal(SIGCONT, sig_handler) == SIG_ERR)
        printf("can't catch SIGCONT\n");
    FILE* f = fopen(argv[1], "w+");
    int fd = fileno(f);
    pid_t pid = getpid();
    int i = 0;
    long n = 10;
    while (flock(fd, LOCK_EX) == 0) {
        printf("\nWriter flock (PID=%d)\n", pid);
        fflush(NULL);
        while (i < n)
            fprintf(f, "%d\n", i++);
        n += 10;
        rewind(f);
        flock(fd, LOCK_UN);
        pause();
    }
    fclose(f);
    return 0;
}

