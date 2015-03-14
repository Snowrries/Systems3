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
	Indexee toDel = (Indexee) a;
	free(toDel);
}

void* StructFill(void* toks, void* buk){
	char* tok = (char*) toks;
	SortedListPtr Bucket = buk;
	Indexee newInd = (Indexee) malloc(sizeof(Indexee));
	newInd->Index = Bucket;
	newInd->token = tok;
	return newInd;

}


void dirTrav(const char* path,RadixPtr root){

		DIR *directory;
		Reader fileread;
		char* tok;
		char* newPath;
		int pathLen;
		int nextlen;


		char *desu;
		size_t bufflen;
		bufflen = 30;
		desu = malloc(bufflen*sizeof(char));

		if(readlink(path, desu, bufflen)!= -1){

			/*It's a symlink!*/
			while(bufflen == readlink(path, desu, bufflen)){
				bufflen += 10;
			}

			dirTrav(desu, root);
		}
		if(errno == EACCES){
			printf("File permissions insufficient.");
			return;
		}
		else if(errno == ENOENT){
			printf("Uhoh, the file's gone. Please check inputted filename and question file's existentiality.");
			return ;
		}


//Directory traverse
	if(strcmp(path, "..") != 0){
		return;
	}

	struct stat *info = (struct stat*) malloc(sizeof(struct stat));
	stat(path,info);
	if(S_ISREG(info->st_mode) && fakemain(&path) == 1){
		fileread = CreateReader(path);
		while((tok = tokenize(fileread)) != NULL){

			InsertStringtoTree(root,tok,path);

		}
		return;

	}
	directory = opendir(path);
	struct dirent *nextDir;

	while((nextDir = readdir(directory))){
		newPath = (char*)malloc((strlen(path) + strlen(nextDir->d_name)+1) *sizeof(char));


	pathLen = strlen(path);
	strncpy(newPath,path,pathLen);
	newPath[pathLen] = '/';
	pathLen++;
	newPath[pathLen] = '\0';
	nextlen = strlen(nextDir->d_name);
	strncat(newPath,nextDir->d_name,nextlen);
	path = newPath;
	dirTrav(path,root);
	free(newPath);
	}
	closedir(directory);
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
	ACertainScientificRailgun = Root;
	char token[30];
	token[0]= 0;
	PreorderTraverse(ACertainScientificRailgun,token,ACertainMagicalIndex,a);
	iter = SLCreateIterator(ACertainMagicalIndex);
	fprintf(output,"{ \"list\" : [ \n");
	while(iter != NULL){
		item = (Indexee)SLGetItem(iter);
		fprintf(output,"\t\t { \"%s\" : [ \n", item->token );
		BucketIter = SLCreateIterator(item->Index);
		while(BucketIter != NULL){
			Bucket = (IndexPtr) SLGetItem(BucketIter);
			fprintf(output,"\t\t{ \"%s\" : %d }\n",Bucket->file,Bucket->freq);
			SLNextItem(BucketIter);
		}
		fprintf(output,"\t ]} \n");

		SLNextItem(iter);
	}
	fprintf(output,"]}");
	fclose(output);
	return;
}




void InsertStringtoTree(RadixPtr Root,char* token,const char* path){
		InserttoTree(Root,Root->Child,token,path);

}

