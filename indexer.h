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
#include <string.h> /* for strerror */
/* Borrowed from ascmagic.c in the file source tree */

#define Fii 0   /* character never appears in text */
#define Tii 1   /* character appears in plain ASCII text */
#define Iii 2   /* character appears in ISO-8859 text */
#define Xii 3   /* character appears in non-ISO extended ASCII (Mac, IBM PC) */

#define FR_BUFSIZ 4096



/*
 * This struct is used to store data retrieved from the tree
 */
struct Indexee{
	char* token;
	SortedListPtr Index;
};

typedef struct Indexee* Indexee;


/*Given a file*, returns 1 if the file is ASCII, 0 if not.*/
 
//int looksascii(FILE* mememe);


/*
 * CompareIndex is used by the RadixTree so that it can create a sorted list
 * of Indexee structs
 * It is a pseudocompare since the tree is already sorted
 * Returns 1
 */
int CompareIndex(void*,void*);

void DestroyIndex(void*);

/*
 * Function that is used by the radix tree so that it can create Indexee
 * and fill into the SortedList
 */
void* StructFill(void*,void*);

void InsertStringtoTree(RadixPtr,char*,const char*);

/*Retrieves index from tree and writes it to a file
 * Input:Root Ptr of tree, and desired file to write to
 * Output: None, but writes a file
 */
void writetofile(RadixPtr,char* file);

/*
 * Traverses through a directory
 * if a file is found it will be tokenized and stored into the tree
 * if a symlink is detected, it will follow if n == 1, and ignore if n == 0
 * Input: Path, RootPtr, parameter n
 * Outout: None
 */
void dirTrav(const char *path, RadixPtr root, int n);


#endif
