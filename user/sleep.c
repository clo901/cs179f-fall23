#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int i, n;

  // Check if the user provided the required argument
  if(argc < 2)
  { 
    //Prints amount of sleep ticks
    printf("Usage: sleep <number of ticks>...\n");

    //Exit program
    exit();
  }

  // Loop through each argument provided by the user
  for(i = 1; i < argc; i++)
  {
    // Convert the argument to an integer
    n = atoi(argv[i]);

    // Print a message indicating how long the program will sleep     
    printf("sleep: sleeping for %d ticks\n", n);
    
    // Sleep for the specified number of ticks
    sleep(n);

    // Attempt to delete the file specified by the argument 
    if(unlink(argv[i]) < 0)
    {
     // If the file could not be deleted, print an error message and exit the loop
      printf("rm: %s failed to delete\n", argv[i]);

      break;
    }
  }

  //Exit program
  exit();
}
