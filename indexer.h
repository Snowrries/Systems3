#ifndef indexer_h
#define indexer_h

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "tokenizer.c"


struct input{
	int fd;
	char buffer[2048];
	int length;
	int used;
};

struct token{

};

struct object{
	char* file;
	int frequency;

};

struct tokens{
	char* key;
	struct object* object;

};

void resetinput(struct input *, int);

char readinput(struct input*);

int isBinary(char*);

//Hashtable stuff somewhere here


#endif
