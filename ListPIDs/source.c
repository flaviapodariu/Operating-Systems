#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <kvm.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <string.h>
//---------GLOBAL VARIABLES ZONE-----------------------------
struct kinfo_proc *kinfo;
int nentries;
char** tree;
int max_depth = 1;
//--------------------------------------

void DFS(pid_t current_proc, int level)
{
    max_depth = (max_depth < level)? level: max_depth;
    int i;
    for(i = 0; i < nentries; i++)
       if(kinfo[i].p_ppid == current_proc)
       {
         printf("Level:%d, PID:%d, PPID:%d, Name:%s, Stats:%d\n ",level,kinfo[i].p_pid,
kinfo[i].p_ppid, kinfo[i].p_comm, kinfo[i].p_stat);
         char* temp_buffer = (char*)malloc(sizeof(char)*10);
         snprintf(temp_buffer,sizeof(temp_buffer), "%d",
kinfo[i].p_pid);

         strncat(tree[level],temp_buffer, strlen(temp_buffer));
         strncat(tree[level], " ", 1);
         free(temp_buffer);
         DFS(kinfo[i].p_pid, level + 1);
       }

}

int
main(void)
{
  char errbuf[_POSIX2_LINE_MAX];
  kvm_t *kernel = kvm_openfiles(NULL, NULL, NULL, KVM_NO_FILES, errbuf);
  if(kernel == NULL)
  {
    printf("%s\n", errbuf);
    return 0;
 int i;
//select a parent process
  kinfo = kvm_getprocs(kernel, KERN_PROC_ALL, 0,sizeof(struct kinfo_proc), &nentries);
  if(kinfo == NULL)
  {
    printf("Could not get processes.");
    return 0;
  }
  tree = (char**)malloc(sizeof(char)*nentries);

  for(i = 0; i < nentries; i++)
    tree[i] = (char*)malloc(sizeof(char)*100);

  for(i = 0; i < nentries; ++i)
   {
     if(strcmp(kinfo[i].p_comm, "init") == 0)
         break;
   }
// get the parent's children processes
  pid_t parent = kinfo[i].p_pid;



//start DFS on children processes
//print processes line by line in DFS order
  printf("Children processes of %s - PID %d, in DFS order\n", kinfo[i].p_comm,
kinfo[i].p_pid);
  DFS(parent, 1);
  printf("\n\n");

//print tree of pids

  printf("LEVEL 0 (PARENT) -> %d\n", kinfo[i].p_pid);
  for(i = 1; i < max_depth; i++)
     printf("LEVEL %d -> %s\n",i, tree[i]);


  free(kinfo);
  free(tree);
  return 0;
}
