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
struct RadixNode {

	char* string;
	int len;
	SortedListPtr Index;
	struct RadixNode *Child;
	struct RadixNode *Next;
	struct RadixNode * Parent;
};

struct Index {
	char* file;
	int freq;

};

typedef struct RadixNode* RadixPtr;

typedef struct Index* IndexPtr;

typedef int (*cmptype)(void*, void*);

typedef void (*deltype)(void*);

typedef void* (*StructFiller)(void*, void*);
/*
 * Initialize a Node for the Radix Tree
 * Input: A char* Token String and Length of Token
 *
 * string: Contains Prefix Str
 * len: Contains len of Prefix Str
 * Child: Contains Pointer to Child of Node
 * Index: SortedListPtr Contains File/Freq Information/ Cannot be used in Tree
 * Next: Contains Pointer to Next Node
 * Parent: Contains Pointer to Parent Node
 *
 *
 * Output: A RadixNode
 */
RadixPtr RadNodeCreate(char*, int);
/* Intializes a Node for the BucketList
 * Input: String with the file name and length of the string
 * Output: A IndexNode
 */
IndexPtr IndexNodeCreate(const char*);
/*
 * Constructs a RadixTreePtr
 * Input: None
 * Output: RootPtr of RadixTree
 */
RadixPtr MakeLikeATree(); //and leaf

/*Inserts the token into the Tree
 *Input: Node of Parent Node and Child Node desired to insert
 *Output: Returns a SortedListPtr which contains information for File/Freq
 */
SortedListPtr *InsertToken(RadixPtr, char*);

/*Compares Two Strings and Finds Length of the matching prefix
 * Input: String to Compare to, String desired to be inserted, Length of Key, Length of insertstring
 * Output: Length of matching prefix characters
 */
int PrefixFinder(char *, char*, int, int);

/*Compares two Keys contained two Nodes; Used for Sorting
 * Input: Two Tree Nodes
 * Output: if Key>Token return >0 , Key<Token return <0, Equal return 0
 */

int CompareNodes(RadixPtr, RadixPtr);

/*Compares two Keys contained two BucketNodes; Used for Sorting files
 * Input: Two Bucket Nodes
 * Output: if Key>Token return >0 , Key<Token return <0, Equal increment Freq and return 0
 */
int CompareBucket(void*, void*);

/*Destruct function for SLBuckets Nodes
 * Input: A Bucket Node
 * Output: None but destroys a node
 */
void SLBucketDestroy(void*);

/*
 * Destroys the Tree
 * Input: Root Ptr of Tree
 * Output: None
 */
void TreeDestruct(RadixPtr root);

/*
 * Traverses through the tree
 * Input: RootPtr of Tree, String (Starts out empty)
 * Output: Some sort of Struct that contains token, file, freq info
 *
 */
void PreorderTraverse(RadixPtr, char*, SortedListPtr, StructFiller);

/*Splits a Node to a prefix and suffix/ Suffix becomes a child node
 * Input: Node to Split and Length of the Prefix
 * Output: None but cuts the node
 */
void NodeCutter(RadixPtr, int);

/*Locates the proper location to insert the token; calls Cut accordingly
 *Input: Parent Node, Child Node, token desired to be inputted
 *Output: SortedListPtr Index of File/Freq
 */
void Find(RadixPtr, RadixPtr, char*, const char*);

#endif /* RADIXTREE_H_ */

