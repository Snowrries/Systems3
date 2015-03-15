#ifndef count_H
#define count_H
#include <stdio.h>
#include <stdlib.h>
typedef struct Node * nodeptr;
struct Node{
	size_t data;
	nodeptr next;
};


struct hashtable_with_chaining{
	int rc;/*Stands for running count*/
	nodeptr *keys;
};
typedef struct hashtable_with_chaining* hash;

/*Makes the hashtable of size inputted*/
hash HashCreate(int size);

/*Puts the address in the hashtable if it isn't already inside. 
  Calls exists function*/
void AddValue(size_t address, hash hashtable);

/*returns 1 if the address is already in the table.
  returns 0 if it isn't.
 */
int exists(size_t address, hash hashtable, int key);

/*frees all malloced items in the hashtable*/
void freedom(hash hashtable, int size);


#endif