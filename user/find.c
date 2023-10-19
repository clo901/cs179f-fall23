#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{ 
// static char buf[DIRSIZ+1];
   char *p;
       
       // Find first character after last slash.
         for(p=path+strlen(path); p >= path && *p != '/'; p--)
                ;        
                         p++;
        // Return blank-padded name.
        // if(strlen(p) >= DIRSIZ)
        // return p;
        // memmove(buf, p, strlen(p));
        // memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
        // return buf;                   
         
         return p;
}


// This function searches for a file with the given filename in the directory specified by the path.
void find(char *path, char* filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  // If the current path is the file we are looking for, print the path. 
  if(!strcmp(fmtname(path), filename))
  {
        printf("%s\n", path);
  }

  // Open the directory specified by the path.
  if((fd = open(path, 0)) < 0)
   {
         fprintf(2, "find: cannot open %s\n", path, fd);
         return;
   }
 // Get the status of the directory.
  if(fstat(fd, &st) < 0)
  {
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // If the path is not a directory, close the file descriptor and return.
  if(st.type != T_DIR)
  {
        close(fd);
        return;
  }

  // If the path is too long, print an error message, close the file descriptor and return.
  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
  {
        printf("find: path too long\n");
         close(fd);
        return;
  }

  // Copy the path to the buffer and append a slash to it.
  strcpy(buf, path);
  p = buf+strlen(buf);
  *p++ = '/';

  // Read the directory entries one by one.
  while (read(fd, &de, sizeof(de)) == sizeof(de))
  {
        // If the inode number is 0, continue to the next entry.
        if(de.inum == 0)
        {
                continue;
        }

        // Copy the name of the entry to the buffer.
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        // If the entry is "." or "..", continue to the next entry.
        if(!strcmp(de.name, ".") || !strcmp(de.name, ".."))
        {
                continue;
        }

        // Recursively call the find function with the new path.
        find(buf, filename);
   }
  // Close the file descriptor.
  close(fd);
}

int main(int argc, char *argv[])
{

  // Check if the arguments are valid.
  if(argc < 2)
  {
    printf("Usage: find path filename\n");
    exit();
  }

  // Call the find function with the specified path and filename.
  find(argv[1], argv[2]);

  //Exit program
  exit();
}
