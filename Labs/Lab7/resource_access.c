#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#define MAX_RESOURCES 5
#define NO_THREADS 15

int available_resources = MAX_RESOURCES;

pthread_mutex_t mutex;  //global mutex

int decrease_count(int count)
{
    if (available_resources < count)
        return -1;
    else
        {
            pthread_mutex_lock(&mutex);
            available_resources -= count;
            printf("Got %d resources %d remaining\n", count, available_resources);
            pthread_mutex_unlock(&mutex);
        }

    return 0;
}

int increase_count(int count)
{   
    pthread_mutex_lock(&mutex);
    available_resources += count;
    printf("Released %d resources %d remaining\n", count, available_resources);
    pthread_mutex_unlock(&mutex);

    return 0;
}
void* resource_manager(void* arg)
{
    int count = *(int*) arg;

    decrease_count(count);
    // sleep(0.5);
    increase_count(count);
 
}

int main()
{
   printf("MAX_RESOURCES=%d\n", MAX_RESOURCES);

   if (pthread_mutex_init(&mutex, NULL))
   {
       perror(NULL);
       return errno;
   }
   pthread_t threads[NO_THREADS];
   int resources[NO_THREADS];
   for(int i = 0 ; i < NO_THREADS; i++)
   {   
       resources[i] = rand() % MAX_RESOURCES + 1;
       if(pthread_create(&threads[i], NULL, resource_manager, &resources[i]))
       {
           perror(NULL);
           return errno;
       }
   }

   for(int i = 0 ; i < NO_THREADS; i++)
   {
       if(pthread_join(threads[i], NULL))
       {
           perror(NULL);
           return errno;
       }
   }
  pthread_mutex_destroy(&mutex);
    return 0;
}
