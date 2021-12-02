#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
void* reverse(void* arg)
{
   char* word = (char*)arg;
   char* rev_word = (char*)malloc(sizeof(char*) * strlen(word));
   for(int i = strlen(word) - 1, j = 0; i >=0; i--, j++)
       rev_word[j] = word[i];

    return (void*)rev_word;
}

int main(int argc, char** argv)
{
  pthread_t thread;
  if(pthread_create(&thread, NULL, reverse, argv[1]))
  {
      perror("Could not create thread");
      return errno;
  }

  void* ret_value;
  if(pthread_join(thread, &ret_value))
  {
      perror(NULL);
      return errno;
  }

  else 
      printf("%s", (char*)ret_value);
  
    return 0;
}
