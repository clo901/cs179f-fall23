#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    // Initialize variables
    int temp  = 0;
    int _argc = 1;
    char *_argv[MAXARG];
    char buffer;
    int i = 0;

    // Check if the first argument is "-n"
    if(strcmp(argv[1], "-n") == 0)
    {
        temp = 3;
    }

    else
    {
        temp = 1;
    }

    // Copy the command to _argv[0]
    _argv[0] = malloc(strlen(argv[temp]) + 1);
    strcpy(_argv[0], argv[temp]);

    // Copy the rest of the arguments to _argv
    for(int i = temp + 1; i < argc; ++i)
    {
        _argv[_argc] = malloc(strlen(argv[i]) + 1);
        strcpy(_argv[_argc++], argv[i]);
    }

    // Allocate memory for the buffer
    _argv[_argc] = malloc(128);

    // Read input from stdin
    while(read(0, &buffer, 1))
    {
        // Check if the input is a newline character
        if(buffer == '\n')
        {
            // Terminate the buffer with a null character
            _argv[_argc][i++] = '\0';

            // Fork a new process and execute the command
            if(fork() == 0)
            {
                exec(argv[temp], _argv);
            }

            else
            {
                // Reset the buffer index and wait for the child process to finish
               i = 0;
               wait();
            }
        }
      
        else
        {
            // Add the input character to the buffer
            _argv[_argc][i++] = buffer;
        }
    }

    // Exit the program
    exit();
}
