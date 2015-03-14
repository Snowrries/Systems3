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


void writetofile(RadixPtr Root,char* file){
	FILE* output = fopen(file,"w");
	SortedListPtr ACertainMagicalIndex;
	RadixPtr ACertainScientificRailgun;
	SortedListIteratorPtr iter;
	ACertainScientificRailgun = MakeLikeATree();
	char token[30];
	token[0]= 0;
	//ACertainMagicalIndex = PreorderTraverse(ACertainScientificRailgun,token);
	iter = SLCreateIterator(ACertainMagicalIndex);

	while(iter != NULL){

		//fprintf(output, )
	}
}


void tokenizer(char* path){
	  FILE* file = fopen(path, "r");
	    if (file == NULL) {
	        return;
	    }
	    struct input *ReadFile = (struct input*)malloc(sizeof(struct input));
	    if (ReadFile== NULL) {
	        return;
	    }
	    ReadFile->fd = fileno(file);
	    ReadFile->length = 0;
	    ReadFile->used = 0;
	    char c;
	    int i = 0;

	    c = readinput(ReadFile);

	    while(!isalnum(c)){
	    	c = readinput(ReadFile);
	    }

}

void InsertStringtoTree(RadixPtr Root,char* token,char* path){
		InsertLocator(Root,Root->Child,token,path);

}

