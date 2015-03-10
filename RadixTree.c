/*
 * RadixTree.c
 *
 *  Created on: Mar 10, 2015
 *      Author: Anthony
 */


#include "radixtree.h"

void RadNodeCreate(char* str, int length){
	RadixPtr newNode = (RadixPtr) malloc(sizeof(struct RadixNode));

	newNode->string = str;
	newNode->len = length;
	newNode->Next = NULL;
	newNode->Child = NULL;

}


void MakeLikeATree(){

}

int prefix(char * key,char* insert,int keylen,int insertlen){
	int i;
	for(i = 0; i < keylen; i ++){
		insert++;
		key++;
		if(i == insertlen ||strncmp(key,insert,i) != 0){
			return i;
		}

	}
	return keylen;
}




