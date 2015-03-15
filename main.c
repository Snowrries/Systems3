/*
 * main.c
 *
 */
#include "indexer.h"
#include <errno.h>
#include "isascii.h"




int main(int argc, char** argv){
	RadixPtr ygg;
	int n;
	char *filnam;
	if(argc !=4){
		printf("Invalid Numbers of Arguments\n");
		return 0;
	}
	filnam = argv[1];
	n = atoi(argv[3]);

	if(n != 0 && n != 1){
		printf("Please enter 0 or 1 as the third parameter. 0 if you would not like to follow Symbolic Links, 1 if you would.\n");
		return 0;
	}
	char userinput[32];
	if(access(argv[1], F_OK) != -1){
		printf("The file already exists.  Would you like to overwrite? (Yes or No)\n");
		scanf("%s", userinput);
	while((strcmp(userinput,"Yes") &&  strcmp(userinput,"No"))){
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

	printf("File will be overwritten\n");
	}
	if(access(argv[2], F_OK) == -1){
		printf("File or Directory does not exist");
		return 0;
	}


	ygg = MakeLikeATree();
	dirTrav(argv[2], ygg, n);
	writetofile(ygg,filnam);
	TreeDestruct(ygg);
	
	return 0;

}

