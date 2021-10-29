#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int count_occurrences(const char* text, const char* word)
{
   int ans = 0;
   char *text_cp = (char *)malloc((strlen(text)+1)*sizeof(char));
   text_cp = strcpy(text_cp, text);
   char *p = strtok(text_cp, " ");
   
   while(p != NULL)
   { 
     if(strcmp(p, word) == 0)
        ans++;
        
   p = strtok(NULL, " ");
   }
   
   return ans;
   
}


int main()
{
   const char* text = "ala bala Portocala alab ala";
   const char* word = "ala";
   int nr = count_occurrences(text, word);
   printf("%d", nr);
   printf("\n");
   return 0;    
}

