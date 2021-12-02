#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#define NO_THREADS 15

pthread_mutex_t mutex;  //global mutex
int threads_at_barrier;
sem_t sem;

int barrier_point()
{
 pthread_mutex_lock(&mutex);
 threads_at_barrier++;
 pthread_mutex_unlock(&mutex);

 if(threads_at_barrier == NO_THREADS)
 {
     for(int i = 0; i < threads_at_barrier; i++)
         sem_post(&sem);
 }
 else 
 if(sem_wait(&sem))
 {
     perror(NULL);
     return errno;
 }
  return 0;
}
//----------thread parent function---------------

void *tfun(void *arg)
{
    int tid = *(int*)arg;
    
    printf("%d reached the barrier\n ", tid);
    barrier_point();
    printf("%d passed the barrier\n ", tid);
    return NULL;
}


int main()
{
    printf("NTHRS=%d\n", NO_THREADS);
    pthread_t threads[NO_THREADS];

   //-----------mutex init----------------------
    if (pthread_mutex_init(&mutex, NULL))
    {
        perror(NULL);
        return errno;
    }
    //-----------semaphore init-----------------
    int S = 0;
    if (sem_init(&sem, 0, S))
    {
        perror(NULL);
        return errno;
    }
    //-----------create threads-----------------
    int index[NO_THREADS];
    for (int i = 0; i < NO_THREADS; i++)
    {
        index[i] = i + 1;
        void *arg = index + i;
        if (pthread_create(&threads[i], NULL, tfun, arg))
        {
            perror(NULL);
            return errno;
        }
    }
    //-----------wait threads-------------------
    for (int i = 0; i < NO_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            perror(NULL);
            return errno;
        }
    }

   pthread_mutex_destroy(&mutex);
   sem_destroy(&sem);
   return 0;
}
