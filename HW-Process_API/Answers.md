# Answers
1. The value will still be x in the child process. And the x will be changed separately in child and parent processes. See q1.c file.
2. Yes, they both can access the file descriptor. They can both write to the file concurrently at same time, and in my experiment parent will complete first. See q2.c file.
3. Calling wait() is workable. I try to sleep the parent process 1 second, and it also works. See q3.c file.
4. See q4.c file. I think these different callings are for different input format which can be used in different cases.
5. The wait() calling will return the child PID. If use wait() in child, I think the child process will not wait since there is no sub-child process. See q5.c file.
6. See q6.c file. The waitpid() calling provides more options. When there is more than one child process, it will be useful.
7. See q7.c file. Child process will not print after close the standard output.
8. See q8.c file.
