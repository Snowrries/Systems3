/*
 * main.c
 *
 */
#include "tokenizer2.h"


int main(int argc, char** argv){
	const char* filename;
	char* deer;
	Reader ogod;
	if(argc !=2){
		printf("Invalid Numbers of Arguments\n");
		return 0;
	}
	filename = argv[1];
	ogod = CreateReader(filename);
	while((deer = tokenize(ogod)) != NULL{
		printf("%s\n",deer);
	}

}
