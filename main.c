/*
 * main.c
 *
 */
#include "indexer.h"
#include <errno.h>
#include "isascii.h"
#include "tokenizer.h"

int main(int argc, char** argv){
	RadixPtr ygg;
	
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
	ygg = MakeLikeATree();
	dirTrav(argv[2], ygg);
	writetofile(ygg,argv[1]);
	TreeDestruct(ygg);
	
	return 0;

}
