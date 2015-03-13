/*
 * RadixTree.h
 *
 *  Created on: Mar 10, 2015
 *      Author: Anthony
 */

#ifndef RADIXTREE_H_
#define RADIXTREE_H_

#include"sorted-list.h"
#include <stdio.h>
#include <string.h>

struct RadixNode{

	char* string;
	int len;
	SortedListPtr Index;
	struct RadixNode *Child;
	struct RadixNode *Next;
	struct RadixNode * Parent;
};



typedef struct RadixNode* RadixPtr;

typedef void* (*StructFiller)(void*,void*);

RadixPtr RadNodeCreate(char*,int);

RadixPtr MakeLikeATree(); //and leaf

SortedListPtr InsertToken(RadixPtr,char*);

int PrefixFinder(char *,char*,int,int);

int CompareNodes(RadixPtr,RadixPtr);

void TreeDestruct();

void PreorderTraverse(RadixPtr,SortedListPtr,StructFiller,char*);

void NodeCutter(RadixPtr,int);

void InsertLocator(RadixPtr,RadixPtr,char*);


#endif /* RADIXTREE_H_ */




