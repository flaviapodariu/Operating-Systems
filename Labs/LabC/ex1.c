#include<stdio.h>
#include<stdlib.h>
int main()
{
     int n, i, j, **m;
     scanf("%d", &n);
     
     m = (int **) malloc(n* sizeof(int *));
     for(i = 0; i < n; i++)
     {
        *(m+i) = (int *) malloc(n* sizeof(int *));
        for(j = 0; j < n; j++)
           scanf("%d", (*(m + i)+j) );
     }
     
     
     // afisare toate elementele
     for(i = 0; i < n; i++)
      {  
         for(j = 0; j < n; j++)
           printf("%d ", *(*(m + i)+j));
           
         printf("\n");  
      }
     
     // afisare element la intersectia diagonalelor
     
     if(n % 2 != 0)
     { printf("Elementul de la intersectia diagonalelor: ");
       printf("%d", *(* (m + (n/2) )+ (n/2)));
       printf("\n");
     }
       
     
     
     // afisare diagonale
     
     // afisare diagonala principala
     printf("Diagonala principala: ");
     for(i = 0 ; i < n ; i++)
        printf("%d ", *(*(m+i) + i));  
     printf("\n");
        
     // afisare diagonala secundara
     
     printf("Diagonala secundara: ");
      for(i = 0 ; i < n ; i++)
        printf("%d ", *(*(m + i) + (n-i-1) ));
     printf("\n");
        
     
     return 0;
}
