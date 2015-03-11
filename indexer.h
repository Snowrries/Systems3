#ifndef indexer_h
#define indexer_h

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "count.h"
#include "tokenizer.c"
#include "RadixTree.h"
#include "sorted-list.h"

struct input{
	int fd;
	char buffer[2048];
	int length;
	int used;
};



struct object{
	char* file;
	int frequency;

};

typedef struct object* FrqPathPtr;

void resetinput(struct input *, int);

char readinput(struct input*);


void InsertStringtoTree(RadixPtr,struct object*);


void tokenizer(char* path, struct hash **hashslingslasher);

int CompareStrings(void* , void*);

void Destruct(void* a);
//Hashtable stuff somewhere here


#endif
