/*
 * main.c
 *
 *  Created on: Mar 10, 2015
 *      Author: Anthony
 */
#include "indexer.h"
int main(int argc, char** argv){
	if(argc !=3){
		printf("Invalid Numbers of Arguments");
		return 0;
	}
	char userinput[32];
	if(access(argv[1], F_OK) != -1){
		printf("The file already exists.  Would you like to overwrite? (Yes or No)");
		scanf("%s", userinput);

	if(strcmp(userinput,"No") == 0 ){
		printf("Exiting \n");
		return 0;
	}
	else if(access(argv[1],W_OK) == -1){
		printf("Cannot write to file.");
		return 0;
	}
	printf("File will be overwritten");
	}
	if(access(argv[2], F_OK) == -1){
		printf("File or Directory does not exist");
		return 0;
	}

	return 0;

}
/*#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
int
main (void)
{
  DIR *dp;
  struct dirent *ep;

  dp = opendir ("./");
  if (dp != NULL)
    {
      while (ep = readdir (dp))
        puts (ep->d_name);
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  return 0;
}


#include <stdio.h>
#include <dirent.h>
static int
one (const struct dirent *unused)
{
  return 1;
}

int
main (void)
{
  struct dirent **eps;
  int n;

  n = scandir ("./", &eps, one, alphasort);
  if (n >= 0)
    {
      int cnt;
      for (cnt = 0; cnt < n; ++cnt)
        puts (eps[cnt]->d_name);
    }
  else
    perror ("Couldn't open the directory");

  return 0;
}


char *
readlink_malloc (const char *filename)
{
  int size = 100;
  char *buffer = NULL;

  while (1)
    {
      buffer = (char *) xrealloc (buffer, size);
      int nchars = readlink (filename, buffer, size);
      if (nchars < 0)
        {
          free (buffer);
          return NULL;
        }
      if (nchars < size)
        return buffer;
      size *= 2;
    }
}
*/