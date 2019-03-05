#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sched.h> 
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	// Make the process only run in CPU-0
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	if (sched_setaffinity(0, sizeof(mask), &mask) < 0) {
		perror("sched_setaffinity");
	}

	// Measure the time cost in a simple system call(0-byte read)
	struct timeval start, end;
	gettimeofday(&start, NULL);
	char data[0];
	for(int i = 0; i < 100000; i++) {
		read(0, data, 0);
	}

	gettimeofday(&end, NULL);
	float time = end.tv_usec - start.tv_usec;
	printf("Average time cost in 0-byte read is: %f usec\n", time/100000);


	// Measure the time cost of a context switch
	int firstpipe[2];
	int secondpipe[2];
	int timepipe[2];
	char buffer_parent[100];
	char buffer_child[100];

	if(pipe(firstpipe) < 0) {
		fprintf(stderr, "parent: Failed to create firstpipe\n");
		return -1;
	}
	if (pipe(secondpipe) < 0) {
		fprintf(stderr, "parent: Failed to create secondpipe\n");
		return -1;
	}
	if (pipe(timepipe) < 0) {
		fprintf(stderr, "parent: Failed to create timepipe\n");
		return -1;
	}	


	int p = fork();
	if (p < 0) {
		// fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);	
	} else if (p == 0) {
		// child process
		printf("Child process ---> %d\n", getpid());
		char message[] = "message from child\n";

		for(int n = 0; n < 5; n++) {
			read(firstpipe[0], buffer_child, sizeof(buffer_child)); //read message from parent process
			printf("%s\n", buffer_child);
			write(secondpipe[1], message, sizeof(message)); // write messege in child process 
		}
		gettimeofday(&end, NULL);
		write(timepipe[1], &end, sizeof(end));


	}
	else {
		// parent process
		printf("parent process ---> %d\n", getpid());
		char message[] = "message from parent\n";
		gettimeofday(&start, NULL);

		for(int n = 0; n < 5; n++) {
			write(firstpipe[1], message, sizeof(message)); //write message in parent process
			read(secondpipe[0], buffer_parent, sizeof(buffer_parent)); //read message from child process
			printf("%s\n", buffer_parent);
		}
		read(timepipe[0], &end, sizeof(end));
		wait(NULL);
		float time = (end.tv_usec - start.tv_usec) / 5;
		printf("contex switch time between two processes: %f usec\n", time);


	}

	return 0;
}