/*
 * indexer.c
 *
 *  Created on: Mar 8, 2015
 *      Author: Anthony
 */

#include "indexer.h"

/*
 *
 */
int CompareIndex(void* a,void* b) {
	return 1;
}

void DestroyIndex(void* a){

}

void* StructFill(void* toks, void* buk){
	char* tok = (char*) toks;
	SortedListPtr Bucket = buk;
	Indexee newInd = (Indexee) malloc(sizeof(Indexee));
	newInd->Index = Bucket;
	newInd->token = tok;
	return newInd;

}

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
	SortedListIteratorPtr BucketIter;
	Indexee item;
	IndexPtr Bucket;
	StructFiller a = &StructFill;
	ACertainMagicalIndex = SLCreate(CompareIndex,DestroyIndex);
	ACertainScientificRailgun = MakeLikeATree();
	char token[30];
	token[0]= 0;
	PreorderTraverse(ACertainScientificRailgun,token,ACertainMagicalIndex,a);
	iter = SLCreateIterator(ACertainMagicalIndex);
	fprintf(output,"{ \"list\" : [ \n", item->token );
	while(iter != NULL){
		item = (Indexee)SLGetItem(iter);
		fprintf(output,"\t\t { \"%s\" : [ \n", item->token );
		BucketIter = SLCReateIterator(item->Index);
		while(BucketIter != NULL){
			Bucket = (IndexPtr) SLGetItem(BucketIter);
			fprintf(output,"\t\t{ \"%s\" : %d }\n",Bucket->file,Bucket->freq);
			SLGetNext(BucketIter);
		}
		fprintf(output,"\t }} \n");

		SLGetNext(iter);
	}
	fprintf(output,"}}");
	fclose(output);
	return;
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
		InserttoTree(Root,Root->Child,token,path);

}

