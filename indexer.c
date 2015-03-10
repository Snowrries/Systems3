/*
 * indexer.c
 *
 *  Created on: Mar 8, 2015
 *      Author: Anthony
 */

#include "indexer.h"




void resetinput(struct input *iptr, int fd){
	iptr->fd = fd;
	iptr->used =0;
	iptr->length=0;
}

char readinput(struct input* iptr){
char c;

if(iptr->used < iptr->length){
	c = iptr->buffer[iptr->used];
	iptr->used ++;
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
	return tolower(c);
}

return 0;
}


/*
void tokenizer(char *path, struct hash **hasher){
	FILE *file = fopen(path, 'r');
	if (file == NULL){
		return;
	}
	int wordLength = 25;
	char* token = (char*) malloc((wordLength+1) * sizeof(char));
	struct input *inputs = (struct input*)malloc sizeof(struct input);
	if(inputs == NULL){
		return;
	}
	char c;
	int fd;
	fd = fileno(file);
	inputs->fd = fd;
	inputs->length=0;
	inputs->used=0;
	int i = 0;
	c = readInput(inputs);
	while(!isalnum(c)){
		c = readINput(inputs);
		if(c == -1){
			free(token);
			free(inputs);
			fclose(file);
			return;
		}
	}

}
*/

int CompareStrings(void* a, void* b){


	return 0;
}

