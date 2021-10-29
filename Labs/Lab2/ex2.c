#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#define BUFFER 4096

int mycp(char* fisier1, char* fisier2)
{
    int fd1, fd2;
    fd1 = open(fisier1, O_RDONLY);
    if(fd1 < 0)
    {
       perror("Input file could not be opened");
       return errno;
    }
    
    fd2 = open(fisier2, O_CREAT | O_RDWR); // ca sa pot verifica daca s-a scris 
    if(fd2 < 0)
    {
       perror("Output file could not be opened");
       return errno;
    }
    
    ssize_t n1, n2;
    char buff[BUFFER+1];
    
    n1 = read(fd1, buff, BUFFER);
    
    while(n1 > 0)
    {  
      n2 = write(fd2, buff, strlen(buff));
      if(n2 < 0)
      {
         perror("File could not be written");
         return errno;
      }
      
      n1 = read(fd1, buff, BUFFER);  
    }
    
    close(fd1);
    close(fd2);
    return 0;

}



int main(int argc, char** argv)
{
  mycp(argv[1], argv[2]);
  return 0;
  
}