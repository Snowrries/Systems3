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

	    c = readInput(ReadFile);

	    while(!isalnum(c)){
	    	c = readInput(ReadFile);
	    }

}

void InsertStringtoTree(RadixPtr Root, FrqPathPtr File,char* token){
	SortedListPtr FileInfo = SLCreate(CompareStrings,Destruct);
	FileInfo = InserttoTree(Root,token);
	if(FileInfo == NULL){
		SLInsert(FileInfo,File);
	}
	else{
		//search for file in sorted list; if found, remove and update and reinput?
		//else insert with freq of one.
		SortedListIteratorPtr popo;
		SortedListIteratorPtr nana;
		if(root == NULL){
				return;
		}
		while(root->Child != NULL){
			if(root->Index->??????????????????????????????????????????????????????)
			TreeDestruct(root->Child);
			root->Child == NULL;
		}
		while(root->Next!=NULL){
			TreeDestruct(root->Next);
			root->Next = NULL;
		}
		SLDestroy(root->Index);
		free(root);
		return;
	}
}

