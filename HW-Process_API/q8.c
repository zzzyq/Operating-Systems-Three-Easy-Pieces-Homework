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
    int fd[2];
    char buf[100];
    if(pipe(fd) < 0) {
        exit(0);
    }
    int p1 = fork();
    if (p1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (p1 == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        strcpy(buf, "message from child 1.");
        close(fd[0]);            
        write(fd[1], buf, strlen(buf));
        exit(0);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
           p1, (int) getpid());
    }

    // fork the second child
    int p2 = fork();
    if (p2 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (p2 == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        close(fd[1]);                
        read(fd[0], buf, 100);
        // show output from child 1 
        printf("child 2 received: %s\n", buf); 
        exit(0);
    }     
    else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
           p2, (int) getpid());
    }    

    return 0;
}