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

struct hash{
	char* key;
	struct object* object;

};

void resetinput(struct input *, int);

char readinput(struct input*);


void inserttoken(char*path, struct hash **tokenee,char* word);


void tokenizer(char* path, struct hash **hashslingslasher);

int CompareStrings(void* , void*);
//Hashtable stuff somewhere here


#endif
