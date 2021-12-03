#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char** argv)
{
    pid_t pid = fork();

    if(pid < 0)
       return errno;

    else
    if(pid > 0)
      {
          pid_t child_pid = wait(NULL);
          printf("\nChild %d finished.", child_pid);
      }

    else
     {
         long val = strtol(argv[1], NULL, 10);
         printf("%d: ", val);

         while(val != 1)
         {   
             printf("%d ", val);

             if(val % 2 == 0)
                val = val / 2;
             else
                val = 3*val + 1;
         }
         printf("%d", val);
     }
    

    return 0;
}
