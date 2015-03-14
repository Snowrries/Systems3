#ifndef indexer_h
#define indexer_h

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include "isascii.h"
#include "tokenizer2.h"
#include "RadixTree.h"




struct Indexee{
	char* token;
	SortedListPtr Index;
};

typedef struct Indexee* Indexee;

int CompareIndex(void*,void*);

void DestroyIndex(void*);

void* StructFill(void*,void*);

void InsertStringtoTree(RadixPtr,char*,const char*);

void writetofile(RadixPtr,char* file);

void dirTrav(const char*,RadixPtr);


#endif
