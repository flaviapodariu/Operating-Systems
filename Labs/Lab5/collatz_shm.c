#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
int main(int argc, char** argv)
{  
   printf("Starting parent %d\n", getpid()); 

   const char* name = "/shared_mem";
   int shm_fd = shm_open(name, O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
   if(shm_fd < 0)
   {
     perror("Invalid file descriptor");
     return errno;
   }

   size_t page_size = getpagesize();
   size_t shm_size = (argc-1) * page_size;

   if(ftruncate(shm_fd, shm_size) == -1)
   {
     perror("Memory could not be allocated.\n");
     shm_unlink(name);
     return errno;
   }

   void* shm_ptr; //acts like buffer

   for(int i = 1; i < argc; i++)
     { 
        shm_ptr = mmap(NULL, page_size, PROT_WRITE, MAP_SHARED, shm_fd, (i-1)*page_size);
        if(shm_ptr == MAP_FAILED)
         {
           perror("Shared memory mapping failed\n");
           shm_unlink(name);
           return errno;
         }

        pid_t child = fork();  
        if(child == 0)
        {
           long val = strtol(argv[i], NULL, 10);
           shm_ptr += sprintf(shm_ptr, "%d: ", val);
           while(val != 1)
           {   
            shm_ptr += sprintf(shm_ptr, "%d ", val);
             if(val % 2 == 0)
                val = val / 2;
             else
                val = 3*val + 1;
           }
           shm_ptr += sprintf(shm_ptr,"%d\n", val);
           if(i == argc-1)
              shm_ptr += sprintf(shm_ptr, '\0');

           printf("Parent %d Me %d\n", getppid(), getpid());
           exit(0);
         }
        else
        if(child < 0)
           return errno;
      }

      for(int i = 1; i <= argc; i++)
         wait(NULL);
      printf("Parent %d, Me %d\n", getppid(), getpid());

      for(int i = 1; i < argc; i++)
         {
            shm_ptr = mmap(0, page_size, PROT_READ, MAP_SHARED, shm_fd, (i-1)*page_size);
            printf("%s\n", shm_ptr);
         }
      
      munmap(shm_ptr, shm_size);
      shm_unlink(name);
          

   return 0;
}
