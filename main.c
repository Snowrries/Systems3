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

