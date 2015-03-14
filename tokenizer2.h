/*
 * tokenizer2.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Anthony
 */

#ifndef TOKENIZER2_H_
#define TOKENIZER2_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
struct input{
	int fd;
	char buffer[2048];
	int length;
	int used;
};

typedef struct input* Reader;

Reader CreateReader(const char*);

void DestroyReader(Reader);

char* tokenize(Reader);

void resetinput(struct input*, int);

char readinput(struct input*);

#endif /* TOKENIZER2_H_ */
