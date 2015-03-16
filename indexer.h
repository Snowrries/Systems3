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

char text_chars[256] = {
        /*                  BEL BS HT LF    FF CR    */
        Fii, Fii, Fii, Fii, Fii, Fii, Fii, Tii, Tii, Tii, Tii, Fii, Tii, Tii, Fii, Fii,  /* 0x0X */
        /*                              ESC          */
        Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Tii, Fii, Fii, Fii, Fii,  /* 0x1X */
        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x2X */
        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x3X */
        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x4X */
        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x5X */
        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x6X */
        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Fii,  /* 0x7X */
        /*            NEL                            */
        Xii, Xii, Xii, Xii, Xii, Tii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii,  /* 0x8X */
        Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii,  /* 0x9X */
        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xaX */
        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xbX */
        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xcX */
        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xdX */
        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xeX */
        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii   /* 0xfX */
};
/*input: file
 * output: 1 if ascii, 0 if not
 */
int looksascii(const char *meme);

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

#endif
