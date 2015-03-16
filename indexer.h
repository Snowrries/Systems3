#ifndef indexer_h
#define indexer_h

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include "isascii.h"
#include "tokenizer.h"
#include "RadixTree.h"


/*
 * This struct is used to store data retrieved from the tree
 */
struct Indexee {
	char* token;
	SortedListPtr Index;
};

typedef struct Indexee* Indexee;

/*
 * CompareIndex is used by the RadixTree so that it can create a sorted list
 * of Indexee structs
 * It is a pseudocompare since the tree is already sorted
 * Returns 1
 */
int CompareIndex(void*, void*);

void DestroyIndex(void*);

/*
 * Function that is used by the radix tree so that it can create Indexee
 * and fill into the SortedList
 */
void* StructFill(void*, void*);

void InsertStringtoTree(RadixPtr, char*, const char*);

/*Retrieves index from tree and writes it to a file
 * Input:Root Ptr of tree, and desired file to write to
 * Output: None, but writes a file
 */
void writetofile(RadixPtr, char* file);

/*
 * Traverses through a directory
 * if a file is found it will be tokenized and stored into the tree
 * if a symlink is detected, it will follow if n == 1, and ignore if n == 0
 * Input: Path, RootPtr, parameter n
 * Outout: None
 */
void dirTrav(const char *path, RadixPtr root, int n);

/*
 * Checks if a file is an ascii character
 * Input: Path of file to check
 * OUtput:Return 1 if ascii, 0 is otherwise
 */
int is_ascii(const char* filename);

#endif
