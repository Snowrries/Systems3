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
#define REGEXPAT "([a-z]([a-z]|[0-9])*)"


struct TokenizerT_ {
	//char * desu;
	char * wholefile;
	//size_t bufflen;
	FILE* boo;
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

int looksascii(TokenizerT *mememe);

TokenizerT *TKCreate(const char * ts );

void TKDestroy( TokenizerT * tk );

char *TKGetNextToken( TokenizerT * tk );

int TKhasNext(TokenizerT * tk);

#endif //TOKENIZER_H
