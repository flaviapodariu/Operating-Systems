#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t  pid = fork();
    if (pid < 0)
       return  errno;
    else 
    if(pid > 0)
       {   
           printf("My PID=%d, Child PID=%d\n", getppid(), getpid());
           wait(NULL); // wait for child
           printf("Child %d finished", getpid());
       }
    else
     { 
       char *argv[] = {"ls", NULL};
       execve("/bin/ls", argv , NULL);
       perror(NULL);
       
     }
