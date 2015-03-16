/*
 * indexer.c
 *
 */

#include "indexer.h"

int CompareIndex(void* a, void* b) {
	return -1;
}

void DestroyIndex(void* a) {
	Indexee toDel = (Indexee) a;
	free(toDel);
}

void* StructFill(void* toks, void* buk) {
	char* tok = (char*) toks;
	SortedListPtr Bucket = buk;
	Indexee newInd = (Indexee) malloc(sizeof(Indexee));
	newInd->Index = Bucket;
	newInd->token = tok;
	return newInd;

}
int is_ascii(const char *moo){

        FILE* cow;
        int a;
        if((cow = fopen(moo,"r") )){
                while((a=fgetc(cow))!=EOF){
                        if(!(isprint(a) || (iscntrl(a)))){
                                rewind(cow);
                                fclose(cow);
                                return 0;

                        }
                }
        rewind(cow);
        fclose(cow);
        return 1;
        }else {
        fprintf(stderr, "Failed to open file: %s\n", strerror(errno));
        return errno;
        }

        if (cow != 0 && fclose(cow) && errno != 0) {
                fprintf(stderr, "Failed to close file: %s\n", strerror(errno));
                return errno;
        }

        return 0;
}

void dirTrav(const char* path, RadixPtr root, int n) {

	DIR *directory;

	char* newPath;
	char *token;
	TokenizerT *stuff;
	int pathLen;
	int nextlen;

	char *desu;
	size_t bufflen;
	bufflen = 30;
	desu = malloc(bufflen * sizeof(char));

	if (readlink(path, desu, bufflen) != -1) {
		/*It's a symlink!*/
		if (n == 0) { /*Not following symlinks*/
			return;
		}
		while (bufflen == readlink(path, desu, bufflen)) {
			bufflen += 10;
		}

		dirTrav(desu, root, n);
	}
	if (errno == EACCES) {
		printf("File permissions insufficient.");
		return;
	} else if (errno == ENOENT) {
		printf(
				"Uhoh, the file's gone. Please check inputted filename and question file's existentiality.");
		return;
	}

//Directory traverse

	if (strcmp(path, "..") != 0 && strcmp(path + strlen(path) - 2, "..") == 0) {
		return;
	}

	if (strcmp(path, ".") != 0 && strcmp(path, "..") != 0
			&& strcmp(path + strlen(path) - 1, ".") == 0) {
		return;
	}

	struct stat *buf = (struct stat*) malloc(sizeof(struct stat));
	stat(path, buf);

	if (S_ISREG(buf->st_mode) && is_ascii(path) == 0) {

		stuff = TKCreate(path);
		while (TKhasNext(stuff)) {
			token = TKGetNextToken(stuff);

			if (token != NULL) {

				InsertStringtoTree(root, token, path);
			}
		}

		TKDestroy(stuff);
		return;

	} else {
		printf("File is Binary \n");
		return;
	}

	if (path == NULL) {
		return;
	}
	directory = opendir(path);
	struct dirent *nextDir = NULL;
	free(buf);

	while ((nextDir = readdir(directory)) != NULL) {

		newPath = (char*) malloc(
				(strlen(path) + strlen(nextDir->d_name) + 2) * sizeof(char));
		if (newPath == NULL) {
			return;
		}

		pathLen = strlen(path);
		strncpy(newPath, path, pathLen);
		newPath[pathLen] = '/';
		pathLen++;
		newPath[pathLen] = '\0';
		nextlen = strlen(nextDir->d_name);
		strncat(newPath, nextDir->d_name, nextlen);

		dirTrav(newPath, root, n);
		free(newPath);

	}
	free(desu);
	closedir(directory);
}

void writetofile(RadixPtr Root, char* file) {

	FILE* output = fopen(file, "w");
	SortedListPtr ACertainMagicalIndex;

	SortedListIteratorPtr iter;
	SortedListIteratorPtr BucketIter;
	Indexee item;
	IndexPtr Bucket;
	StructFiller ACertainScientificRailgun = &StructFill;
	ACertainMagicalIndex = SLCreate(CompareIndex, DestroyIndex);

	char* token = malloc(sizeof(char) * 30);
	token[0] = '\0';
	PreorderTraverse(Root->Child, token, ACertainMagicalIndex,
			ACertainScientificRailgun);

	iter = SLCreateIterator(ACertainMagicalIndex);
	fprintf(output, "{ \"list\" : [ \n");
	item = (Indexee) SLGetItem(iter);
	while (item != NULL) {

		fprintf(output, "\t\t { \"%s\" : [ \n", item->token);
		BucketIter = SLCreateIterator(item->Index);
		Bucket = (IndexPtr) SLGetItem(BucketIter);
		while (Bucket != NULL) {
			Bucket = (IndexPtr) SLGetItem(BucketIter);
			fprintf(output, "\t\t{ \"%s\" : %d }\n", Bucket->file,
					Bucket->freq);
			Bucket = SLNextItem(BucketIter);
		}
		fprintf(output, "\t ]} \n");
		item = (Indexee) SLNextItem(iter);
	}
	fprintf(output, "]}");
	fclose(output);
	free(token);
	return;
}

void InsertStringtoTree(RadixPtr Root, char* token, const char* path) {
	Find(Root, Root->Child, token, path);

}
