#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i, n;

  if(argc < 2){
    printf("Usage: sleep <number of ticks>...\n");
    exit();
  }

  for(i = 1; i < argc; i++)
  {
    n = atoi(argv[i]);
    printf("sleep: sleeping for %d ticks\n", n);
    sleep(n);
   
    if(unlink(argv[i]) < 0)
    {
      printf("rm: %s failed to delete\n", argv[i]);
      break;
    }
  }
  exit();
}
