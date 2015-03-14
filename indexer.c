/*
 * indexer.c
 *
 *  Created on: Mar 8, 2015
 *      Author: Anthony
 */

#include "indexer.h"

/*
 *
 */
int CompareIndex(void* a,void* b) {
	return 1;
}

void DestroyIndex(void* a){

}

void* StructFill(void* toks, void* buk){
	char* tok = (char*) toks;
	SortedListPtr Bucket = buk;
	Indexee newInd = (Indexee) malloc(sizeof(Indexee));
	newInd->Index = Bucket;
	newInd->token = tok;
	return newInd;

}






void writetofile(RadixPtr Root,char* file){
	FILE* output = fopen(file,"w");
	SortedListPtr ACertainMagicalIndex;
	RadixPtr ACertainScientificRailgun;
	SortedListIteratorPtr iter;
	SortedListIteratorPtr BucketIter;
	Indexee item;
	IndexPtr Bucket;
	StructFiller a = &StructFill;
	ACertainMagicalIndex = SLCreate(CompareIndex,DestroyIndex);
	ACertainScientificRailgun = MakeLikeATree();
	char token[30];
	token[0]= 0;
	PreorderTraverse(ACertainScientificRailgun,token,ACertainMagicalIndex,a);
	iter = SLCreateIterator(ACertainMagicalIndex);
	fprintf(output,"{ \"list\" : [ \n", item->token );
	while(iter != NULL){
		item = (Indexee)SLGetItem(iter);
		fprintf(output,"\t\t { \"%s\" : [ \n", item->token );
		BucketIter = SLCreateIterator(item->Index);
		while(BucketIter != NULL){
			Bucket = (IndexPtr) SLGetItem(BucketIter);
			fprintf(output,"\t\t{ \"%s\" : %d }\n",Bucket->file,Bucket->freq);
			SLNextItem(BucketIter);
		}
		fprintf(output,"\t }} \n");

		SLNextItem(iter);
	}
	fprintf(output,"}}");
	fclose(output);
	return;
}




void InsertStringtoTree(RadixPtr Root,char* token,char* path){
		InserttoTree(Root,Root->Child,token,path);

}

