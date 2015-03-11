/*
 * main.c
 *
 *  Created on: Mar 10, 2015
 *      Author: Anthony
 */
#include "indexer.h"
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
	FILE *b;
	char *desu;
	char *ofst;//Offset
	char *inst; //Insert value in burlapSack
	regex_t patmat;//Pattern matching
	regmatch_t matmat;//matchmat
	
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
	//In other cases, it's just plainly not a simlink. 

	a = opendir(fds);
	if(a == NULL){
		if(errno == ENOTDIR){//Not simlink? Not Dir? We'll assume it's a file.
			b = fopen(fds,"r");
			
			while(getline(&desu, &bufflen, fds) > 0){
				/*regex me?*/
				if(regcomp(&patmat, [a-z]*+([a-z]+[0-9])*,REG_ICASE)!=0){
					printf("ERROR, ERROR. Fix me please. And hurry up about it.");
				}
				ofst = (char *)malloc((1+strlen(b))*sizeof(char *));
				if(regexec(&patmat, b, 1+strlen(b), matmat, 0)==0){
						//It matched~!
						//Here, we put the matches in the data struct. 
						while(rm_so!=NULL){
							inst = malloc((rm_eo - rm_so)*sizeof(char));
							inst = b + rm_so;
							/*Call the insert function!*/
							
						}
						//End loop, line has been processed. 
					}
			
			
			
				//Free reg for use in next line desu. Maybe we can move regcomp out of the loop and free it later? Look into this.
				regfree(&patmat);
			}//I reaaaaaaaaaaaally hope this line's right. If it's broke, check here at some point.
			
		}
		else if(errno == EACCES){
			printf("You haven't the permissions to access this directory.");
		}
		else if(errno == EMFILE){
			printf("The process has too many files open. Consider gastric bypass.");
		}
		else if(errno == ENOMEM){
			printf("Not enough memory... ? What's got your ram in a bunch?")
		}
		
	}
	//So it is a directory! Let's iterate through and recurse everything we find.
	while((c=readdir(a))!= NULL{
		dirTrav(c->d_name, burlapSack);
	}
	//End of journey. Go back to previous frame.
	free(desu);
	closedir(a);
	return 0;
	
}





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
