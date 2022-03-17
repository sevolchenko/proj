#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <string.h>
#define BLOCK 512

int main (int argc, char **argv)
{
     pid_t pid;
     int i;
    /* создание нового процесса */
     pid = fork();
     if (pid == -1)
        return -1;
     else if (pid != 0)
        exit (EXIT_SUCCESS);
    /* создание нового сеанса и группы процессов */
     if (setsid ( ) == -1)
        return -1;

     pid = fork();
     if (pid == -1)
        return -1;
     else if (pid != 0)
        exit (EXIT_SUCCESS);

    /* установка в качестве рабочего каталога корневого каталога */
     if (chdir ("/") == -1)
        return -1;
    /* закрытие всех открытых файлов */
    /* NR_OPEN - это слишком, но это работает */
     for (i = 0; i < INR_OPEN_MAX; i++)
        close (i);
    /* перенаправление дескрипторов файла 0,1,2 в /dev/null */
     open ("/dev/null", O_RDWR); /* stdin */
     dup (0); /* stdout */
     dup (0); /* stderror */

     int fd_read = open("./tmp/data", O_RDONLY);
     int fd_write = open("./tmp/output", O_WRONLY);

     char data[BLOCK];
     int sz;
     while ((sz = read(fd_read, data, sizeof(data)) > 0)) {
         char word[sz];
         strncpy(word, data, sz);
         word[sz] = 0;
         char to_print[BLOCK];
         sprintf(to_print, "Server %d reads : %s\n", getpid(), word);
         write(fd_write, to_print, sizeof(to_print));
     }
     write(fd_write, "EOF\n", 4);
     close(fd_read);
     close(fd_write);
     return 0;
}
