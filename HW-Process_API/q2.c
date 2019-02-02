#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int f = open("./q2_output.txt", O_CREAT|O_WRONLY|O_APPEND);
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        // printf("child x is: %d\n", x);
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char str[] = "child\n";
        write(f, str, sizeof(str));
        close(f);
    } else {
        // parent goes down this path (original process)
        // printf("parent x is: %d\n", x);
        printf("hello, I am parent of %d (pid:%d)\n",
            rc, (int) getpid());
        char str[] = "parent\n";
        write(f, str, sizeof(str));
        close(f);
    }
    return 0;
}