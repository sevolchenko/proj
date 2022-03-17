#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK 512
int main(int argc, char **argv) {
    int status, pipefd[2];
    pipe(pipefd);
    pid_t child_pid = fork();
    int count = atoi(argv[1]);
    switch (child_pid) {
        case -1:
            perror("fork");
            _exit(1);
        case 0:
            for (int i = 0; i < count; i++)
            {
                if (fork() == 0) {
                    close(pipefd[0]);
                    close(STDOUT_FILENO);
                    dup(pipefd[1]);
                    execl("./client", "./client", argv[2], NULL);
                }
            }
            _exit(0);
        default:
            close(pipefd[1]);
            close(STDIN_FILENO);
            dup(pipefd[0]);
            wait(&status);
            execl("./server", "./server ", NULL);
    }
    return 0;
}
