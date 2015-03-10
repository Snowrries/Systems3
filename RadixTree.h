/*
 * RadixTree.h
 *
 *  Created on: Mar 10, 2015
 *      Author: Anthony
 */

#ifndef RADIXTREE_H_
#define RADIXTREE_H_

#include <stdio.h>

struct RadixNode{

	char* string;
	int len;
	RadixPtr Next;
	RadixPtr Child;
};

typedef struct RadixNode* RadixPtr;

void RadNodeCreate(char*,int);

void MakeLikeATree(); //and leaf


int prefix(char *,char*,int,int);

RadixPtr* search(RadixPtr,char*,int n);


#endif /* RADIXTREE_H_ */




