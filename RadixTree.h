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
#include <stdlib.h>
struct RadixNode{

	char* string;
	int len;
	SortedListPtr Index;
	struct RadixNode *Child;
	struct RadixNode *Next;
	struct RadixNode * Parent;
};

struct Index{
	char* file;
	int freq;

};


typedef struct RadixNode* RadixPtr;

typedef struct Index* IndexPtr;

typedef int (*cmptype)(void*, void*);

typedef void (*deltype)(void*);

typedef void* (*StructFiller)(void*,void*);

RadixPtr RadNodeCreate(char*,int);

IndexPtr IndexNodeCreate(char*);

RadixPtr MakeLikeATree(); //and leaf

SortedListPtr *InsertToken(RadixPtr,char*);

int PrefixFinder(char *,char*,int,int);

int CompareNodes(RadixPtr,RadixPtr);

int CompareIndex(void*,void*);

void SLIndexDestruct(void*);

void TreeDestruct();

//void PreorderTraverse(RadixPtr,SortedListPtr,StructFiller,char*);

void PreorderTraverse(RadixPtr,char*);

void NodeCutter(RadixPtr,int);

void InsertLocator(RadixPtr,RadixPtr,char*,char*);


#endif /* RADIXTREE_H_ */




