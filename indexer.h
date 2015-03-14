#ifndef indexer_h
#define indexer_h

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "tokenizer.c"
#include "RadixTree.h"
#include "sorted-list.h"

struct input{
	int fd;
	char buffer[2048];
	int length;
	int used;
};


struct Indexee{
	char* token;
	SortedListPtr Index;
};

typedef struct Indexee* Indexee;
int CompareIndex(void*,void*);

void DestroyIndex(void*);

void* StructFill(void*,void*);

void resetinput(struct input *, int);

char readinput(struct input*);

void InsertStringtoTree(RadixPtr,char*,char*);

void tokenizer(char* path);

void writetofile(RadixPtr,char* file);




#endif
