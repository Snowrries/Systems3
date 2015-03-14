/*
 * main.c
 *
 */
#include "indexer.h"
#include <errno.h>
#include "isascii.h"
#include "tokenizer.h"
/* 	Try to open the const *char as a simlink, then directory, 
	then file if both attempts failed. Use errno judiciously.
	Returns 0 if failure.
	
	This programmer isn't sure how the directory links work- 
	whether they give you the whole thing or just relative addresses
	If it's just relative, we'll need to pass the whole addresses
	every time we call the function, such that we can append it to file name collisions.
	*/
	
int dirTrav(const char *fds, RadixPtr *burlapSack){
	DIR *a;
	struct dirent *c;
	char *desu;
	size_t bufflen;
	bufflen = 30;
	desu = malloc(bufflen*sizeof(char));
	
	if(readlink(fds, desu, bufflen)!= -1){
		
		/*It's a symlink!*/
		while(bufflen == readlink(fds, desu, bufflen)){
			bufflen += 10;
		}
		
		dirTrav(desu, burlapSack);
	}
	if(errno == EACCES){
		printf("File permissions insufficient.");
		return 0;
	}
	else if(errno == ENOENT){
		printf("Uhoh, the file's gone. Please check inputted filename and question file's existentiality.");
		return 0;
	}
	/*In other cases, it's just plainly not a simlink. */

	a = opendir(fds);
	if(a == NULL){
		if(errno == ENOTDIR){/*Not simlink? Not Dir? We'll assume it's a file.*/
			if(fakemain(fds) != 1){/*It's not a text file. */
					free(desu);
					closedir(a);
					return 0;
			}
			//matching(fds);
			//This calls the tokenizerer.
			
		}
		else if(errno == EACCES){
			printf("You haven't the permissions to access this directory.");
		}
		else if(errno == EMFILE){
			printf("The process has too many files open. Consider gastric bypass.");
		}
		else if(errno == ENOMEM){
			printf("Not enough memory... ? What's got your ram in a bunch?");
		}
		
	}

	return 0;
	
}



/*

int main(int argc, char** argv){
	if(argc !=3){
		printf("Invalid Numbers of Arguments");
		return 0;
	}
	char userinput[32];
	if(access(argv[1], F_OK) != -1){
		printf("The file already exists.  Would you like to overwrite? (Yes or No)\n");
		scanf("%s", userinput);
	while((userinput != "Yes") && (userinput !="No")){
		printf("Sorry, didn't quite catch that. Please enter Yes or No.\n");
		scanf("%s", userinput);
	}
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
