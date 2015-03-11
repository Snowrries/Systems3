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



int CompareStrings(void* a, void* b){
	FrqPathPtr First = (FrqPathPtr) a;
	FrqPathPtr Second = (FrqPathPtr) b;
	if(First->frequency > Second->frequency){
		return 1;
	}
	else if(First->frequency == Second->frequency){
		return strcmp(First->file,Second->file);
	}
	return -1;
}

void Destruct(void* a){
	free(a);
}


void InsertStringtoTree(RadixPtr Root, FrqPathPtr File,char* token){
	SortedListPtr FileInfo = SLCreate(CompareStrings,Destruct);
	FileInfo = InserttoTree(Root,token);
	SLInsert(FileInfo,File);
}

