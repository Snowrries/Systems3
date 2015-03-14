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
Reader CreateReader(const char* path){
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
unsigned char c;

if(iptr->used < iptr->length){
	c = iptr->buffer[iptr->used];
	iptr->used ++;
	c = tolower(c);
	return c;
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
	c = tolower(c);
	return c;
}

return 0;
}

char* tokenize(Reader FilePtr){
	//Arbitrary length
	int len = 5;
	char* token =(char*) malloc(sizeof(char) *len);


	unsigned char c;
	int i = 0;
	c = readinput(FilePtr);
	while(!isalpha(c)){
		c = readinput(FilePtr);
		if(c == -1){
			DestroyReader(FilePtr);
			return NULL;
		}
	}
	while(c != -1){
		if(isalnum(c)){
			if(len <= i){
				token = (char*) realloc(token,sizeof(char)*(2*len + 1) );
				len *= 2;
			}

			token[i] = c;
			i++;
		}
	c =readinput(FilePtr);

	}
	token[i] = '\0';
	return token;
}
