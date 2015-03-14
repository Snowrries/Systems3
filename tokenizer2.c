/*
 * tokenizer2.c
 *
 *  Created on: Mar 14, 2015
 *      Author: Anthony
 */


#include "tokenizer2.h"

void resetinput(struct input *iptr, int fd){
	iptr->fd = fd;
	iptr->used = 0;
	iptr->length= 0;
}
Reader CreateReader(char* path){
		FILE* file = fopen(path , "r");
		Reader FilePtr = (Reader) malloc(sizeof(Reader));
		FilePtr->fd = fileno(file);
		FilePtr->length = 0;
		FilePtr->used = 0;
		return FilePtr;

}

void DestroyReader(Reader input){
	close(input->fd);
	free(input);
}

char readinput(struct input* iptr){
char c;

if(iptr->used < iptr->length){
	c = iptr->buffer[iptr->used];
	iptr->used ++;
	return tolower(c);
}

else if ( iptr->length == iptr->used){
	iptr->length = read(iptr->fd, iptr->buffer,sizeof(iptr->buffer));
	if(iptr->length==0){
		iptr->used = 0;
		return -1;
	}

}
else{
	c= iptr->buffer[0];
	iptr->used =1;
	return tolower(c);
}

return 0;
}

char* tokenize(Reader FilePtr){
	//Arbitrary length
	int len = 5;
	char* token =(char*) malloc(sizeof(char) *len);


	char c;
	int i = 0;
	c = readinput(FilePtr);
	while(!isalnum(c)){
		c = readinput(FilePtr);
		if(c == -1){
			DestoryReader(FilePtr);
			return NULL;
		}
	}
	while(c != -1){
		if(isalnum(c)){
			if(len <= i){
				token = (char*) realloc(token,sizeof(char)*(2*len + 1) );
				len *= 2;
			}

			strcat(token,c);
			i++;
		}
	c =readinput(FilePtr);

	}
	token[i] = '\0';
	return token;
}
