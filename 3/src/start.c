#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#define BLOCK 512
int main() {
    int status, pipefd[2];
    pipe(pipefd);
    pid_t child_pid = fork();
    switch (child_pid) {
        case -1:
            perror("fork");
            _exit(1);
        case 0:
            close(pipefd[0]);
            close(STDOUT_FILENO);
            dup(pipefd[1]);
            execl("client", "client", pipefd[1], "Hello", NULL);
        default:
            close(pipefd[1]);
            close(STDIN_FILENO);
            dup(pipefd[0]);
            printf("%d", status);
            wait(&status);
            printf("%d", status);
            execl("server", "server", pipefd[0], NULL);
    }
    return 0;
}