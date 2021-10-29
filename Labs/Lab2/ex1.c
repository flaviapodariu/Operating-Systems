#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
  char str[20] = "Hello World!\n";
  write(1,str, sizeof(str));
  return 0;
}
