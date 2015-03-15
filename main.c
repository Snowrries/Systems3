/*
 * main.c
 *
 */
#include "tokenizer2.h"


int main(int argc, char** argv){
	char* filename;
	FILE* slime;
	char* deer;
	printf("%s",argv[1]);
	Reader ogod;
	if(argc !=2){
		printf("Invalid Numbers of Arguments\n");
		return 0;
	}
	filename = argv[1];
	slime = fopen(filename,"r");
	ogod = CreateReader(slime);
	deer = tokenize(ogod);
	while(deer!= NULL){
		printf("%s\n",deer);
		deer = tokenize(ogod);
	}
	FILE *fp;
   int c;
  
   fp = fopen("file.txt","w+");
   fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
   
   fclose(fp);
   
   
   fp = fopen("file.txt","r");
   while(! feof(fp))
   {
      c = fgetc(fp);
      printf("%c", c);
   }
   fclose(fp);
   return(0);

}
