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
	return -1;
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

void dirTrav(const char* path,RadixPtr root, int n){

		DIR *directory;



		char* newPath;
		char *token;
		TokenizerT *stuff;
		int pathLen;
		int nextlen;

		char *desu;
				size_t bufflen;
				bufflen = 30;
				desu = malloc(bufflen*sizeof(char));

				if(readlink(path, desu, bufflen)!= -1){
					/*It's a symlink!*/
					if(n == 0){ /*Not following symlinks*/
						return;
					}
					while(bufflen == readlink(path, desu, bufflen)){
						bufflen += 10;
					}

					dirTrav(desu, root, n);
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

		  if (strcmp(path, "..") != 0 && strcmp(path+strlen(path)-2, "..") == 0) {
		        return;
		    }

		    if (strcmp(path, ".") != 0 && strcmp(path, "..") != 0 && strcmp(path+strlen(path)-1, ".") == 0) {
		        return;
		    }


	struct stat *buf = (struct stat*) malloc(sizeof(struct stat));
	stat(path,buf);

	if(S_ISREG(buf->st_mode) ){

		stuff = TKCreate(path);
		while(TKhasNext(stuff)){
	                token = TKGetNextToken(stuff);
			printf("indexer: %s\n", token);
	                if(token!=NULL){
//				printf("%s",token);
				InsertStringtoTree(root,token,path);
	                }
		//printf("End of iter\n");
		}
		
		TKDestroy(stuff);
		return;	          
	}




	if(path == NULL){
		return;
	}
	directory = opendir(path);
	struct dirent *nextDir = NULL;
	free(buf);

	while((nextDir = readdir(directory)) !=NULL){

		newPath = (char*)malloc((strlen(path) + strlen(nextDir->d_name)+2) *sizeof(char));
		if(newPath == NULL){
			return;
		}

	pathLen = strlen(path);
	strncpy(newPath,path,pathLen);
	newPath[pathLen] = '/';
	pathLen++;
	newPath[pathLen] = '\0';
	nextlen = strlen(nextDir->d_name);
	strncat(newPath,nextDir->d_name,nextlen);



	        printf("\t %s \t",newPath);
	        dirTrav(newPath, root, n);
	        free(newPath);

}
free(desu);
	closedir(directory);
}

void writetofile(RadixPtr Root,char* file){
	
	FILE* output = fopen(file,"w");
	SortedListPtr ACertainMagicalIndex;

	SortedListIteratorPtr iter;
	SortedListIteratorPtr BucketIter;
	Indexee item;
	IndexPtr Bucket;
	StructFiller ACertainScientificRailgun = &StructFill;
	ACertainMagicalIndex = SLCreate(CompareIndex,DestroyIndex);

	char* token = malloc(sizeof(char)*30);
        token[0] = '\0';
	PreorderTraverse(Root->Child,token,ACertainMagicalIndex,ACertainScientificRailgun);

	iter = SLCreateIterator(ACertainMagicalIndex);
	fprintf(output,"{ \"list\" : [ \n");
	item = (Indexee)SLGetItem(iter);
		while (item !=NULL){

		fprintf(output,"\t\t { \"%s\" : [ \n", item->token );
		BucketIter = SLCreateIterator(item->Index);
		Bucket = (IndexPtr) SLGetItem(BucketIter);
		while(Bucket != NULL){
					Bucket = (IndexPtr) SLGetItem(BucketIter);
					fprintf(output,"\t\t{ \"%s\" : %d }\n",Bucket->file,Bucket->freq);
					Bucket = SLNextItem(BucketIter);
		}
		fprintf(output,"\t ]} \n");
		item = (Indexee)SLNextItem(iter);
	}
		fprintf(output,"]}");
		fclose(output);
		free(token);
		return;
}









void InsertStringtoTree(RadixPtr Root,char* token,const char* path){
		Find(Root,Root->Child,token,path);

}

