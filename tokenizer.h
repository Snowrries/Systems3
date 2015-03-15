/*tokenizer.h*/
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <regex.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "RadixTree.h"
#define REGEXPAT "([a-z]([a-z][0-9])*)"
/*
The function matching uses regex to produce string snippets of each file;
Each snippet begins with an alphabetic character 
followed by any number of alphanumeric characters.
It proceeds to put each match it finds in a tree data structure, 
as described in RadixTree.h

This implementation is not as modular, but is simple 
and reads only one line at a time so large files won't
clutter memory.

Input: a file name, fds.
Output: nothing.

*/

struct TokenizerT_ {
	char* untokened;
	regoff_t charsfromleft;
	int numtoken;
	regmatch_t matches;
	regmatch_t matlol;
	regex_t rx;
	regex_t keywordrx;
	int hasNext;
	int wasModified;
};

typedef struct TokenizerT_ TokenizerT;


TokenizerT *TKCreate( char * ts );

void TKDestroy( TokenizerT * tk );

char *TKGetNextToken( TokenizerT * tk );





#endif TOKENIZER_H