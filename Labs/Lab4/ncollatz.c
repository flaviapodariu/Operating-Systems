#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{ 
   pid_t parent = getpid();
   printf("Starting parent %d\n", getpid()); 

   for(int i = 1; i < argc; i++)
     { 
       pid_t child = fork();  
       if(child == 0)
        {
          long val = strtol(argv[i], NULL, 10);
          printf("%d: ", val);

          while(val != 1)
          {   
            printf("%d ", val);

            if(val % 2 == 0)
               val = val / 2;
            else
               val = 3*val + 1;
          }
          printf("%d\n", val);
          exit(0);
        }
       else
       if(child < 0)
          return errno; 
     }

       while(wait(NULL)>0)
          printf("Done parent %d Me %d\n", getppid(), getpid());

  return 0;
}