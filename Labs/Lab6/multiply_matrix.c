#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

int n, p, m;  //global
//n -> linii mat1, p -> coloane mat1
// p -> linii mat2, m -> coloane mat2


int** mat1; 
int** mat2; 


void* compute(void* numbers)
{
   int lin_mat1 = *(int*)numbers;
   int col_mat2 = *((int*)numbers+1);

   int* sum = (int*)malloc(sizeof(int));
   *sum = 0;
   for(int j = 0 ; j < p; j++)
       *sum += mat1[lin_mat1][j] * mat2[j][col_mat2];

    return (void*)sum;   
   
}

int main()
{
    printf("%s", "Introduceti nr de linii pentru prima matrice:\n");
    scanf("%d", &n);
    printf("%s", "\nIntroduceti nr de coloane pentru prima matrice:\n");
    scanf("%d", &p); 
    printf("%s", "\nNr de linii ale celei de a doua matrice = nr de coloane ale primei matrice:\n");
    printf("%s", "Introduceti nr de coloane pentru a doua matrice:\n");
    scanf("%d", &m);

    printf("Matricea 1 va fi de %d x %d, iar matricea 2 va fi de %d x %d", n, p, p, m);      
                   
    mat1 = (int**)malloc(sizeof(int)*n);
    mat2 = (int**)malloc(sizeof(int)*p);

    int** mat = (int**)malloc(sizeof(int)*n);

   // citire --------------------------------------------
    for(int i = 0; i < n; i++)
      {
         mat1[i] = (int*)malloc(sizeof(int)* p);
         for(int j = 0; j < p; j++)
             scanf("%d", &mat1[i][j]); 
      } 

    for(int i = 0; i < p; i++)
      {
         mat2[i] = (int*)malloc(sizeof(int)* m);
         
         for(int j = 0; j < m; j++)
             scanf("%d", &mat2[i][j]); 
      }
 //-----------------------------------------------------   
    pthread_t thread[n*m]; 

    int nr_elem = 0;
    for(int i = 0; i < n; i++)
     {
         mat[i] = (int*)malloc(sizeof(int)* m); //matr rezultata o sa fie n x m
  
        for(int j = 0 ; j < m; j++)
        {   
            
            int* values = (int*)malloc(sizeof(int)*2);
            values[0] = i;
            values[1] = j;
            void* args = values;
            if(pthread_create(&thread[nr_elem++], NULL, compute, args))
            {
                perror(NULL);
                return errno;
            }
        
        }
           
     }
     nr_elem = 0;
     
     for(int i = 0; i < n; i++)
     {
         for(int j = 0 ; j < m; j++)
          { 
            void* ret_value;
             if(pthread_join(thread[nr_elem++], &ret_value))
              {
                perror(NULL);
                return errno;
              }
             else  
               mat[i][j] = *(int*)ret_value;
          }
     }

    // for(int i = 0; i < n; i++)
    //    free(mat1[i]);
    // for(int i = 0; i < m; i++)   
    //    free(mat2[i]);

     for(int i = 0 ; i < n; i++)
     {
         for(int j = 0 ; j < m; j++)
            printf("%d ", mat[i][j]);
         printf("\n");   
     }

    return 0;
}
