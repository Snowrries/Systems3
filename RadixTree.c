
#include "RadixTree.h"

RadixPtr RadNodeCreate(char* str, int length) {
	RadixPtr newNode = (RadixPtr) malloc(sizeof(struct RadixNode));
	newNode->string = str;
	newNode->len = length;
	newNode->Child = NULL;
	newNode->Index = NULL;
	newNode->Next = NULL;
	newNode->Parent = NULL;
	return newNode;

}

IndexPtr IndexNodeCreate(const char* path) {
	IndexPtr newNode = (IndexPtr) malloc(sizeof(struct Index));
	newNode->file = malloc(sizeof(char) * 64);
	strcpy(newNode->file, path);
	newNode->freq = 1;
	return newNode;

}

RadixPtr MakeLikeATree() {
	RadixPtr headptr = RadNodeCreate(" ", 0);
	return headptr;
}

SortedListPtr *InsertToken(RadixPtr Head, char* token) {

	RadixPtr Obj = RadNodeCreate(token, strlen(token));
	Obj->Parent = Head;

	RadixPtr Child = (Head->Child);
	RadixPtr Prev = (Head);

	int cmpresult;
	if (Child == NULL) {
		Head->Child = Obj;

		return &(Obj->Index);
	}

	//Go through the list of Child Nodes of Parent Node Head
	while (Child != NULL) {

		cmpresult = CompareNodes(Child, Obj);

		if (cmpresult > 0) {
			Obj->Next = Child;
			if (Prev == Head) {
				(Prev)->Child = Obj;
			} else {
				(Prev)->Next = Obj;
			}
			return &(Obj->Index);
		}
		//If there is a duplicate no need to insert Node
		else if (cmpresult == 0) {

			return &(Child->Index);
		}
		Prev = Child;
		Child = (Child)->Next;

	}
	Prev->Next = Obj;
	Child = Obj;
	return &(Obj->Index);
}

int CompareNodes(RadixPtr Key, RadixPtr Token) {

	if (Token->string == NULL) {
		return -1;
	}
	return strcmp(Key->string, Token->string);
}

int CompareBucket(void* K, void* I) {

	IndexPtr Key = (IndexPtr) K;
	IndexPtr Insert = (IndexPtr) I;

	if (Key == NULL) {
		return -1;
	}
	int result = strcmp(Key->file, Insert->file);
	if (result == 0) {
		Key->freq++;
	}
	return result;
}

void SLBucketDestroy(void* Node) {
	IndexPtr Del = (IndexPtr) Node;
	free(Del->file);
	free(Del);

}

void TreeDestruct(RadixPtr root) {

	if (root == NULL) {
		return;
	}
	while (root->Child != NULL) {
		TreeDestruct(root->Child);
		root->Child = NULL;
	}
	while (root->Next != NULL) {
		TreeDestruct(root->Next);
		root->Next = NULL;
	}
	
	SLDestroy(root->Index);
	free(root);
	return;
}

int PrefixFinder(char * key, char* insert, int keylen, int insertlen) {
	int i;

	for (i = 0; i < insertlen; i++) {
		if (i == keylen || strncmp(key, insert, 1) != 0) {

			return i;
		}
		key++;
		insert++;

	}
	return insertlen;
}

void NodeCutter(RadixPtr Node, int length) {

	int sufflen = Node->len - length + 1;
	char* suffix;
	char* prefix;
	suffix = malloc(sizeof(char) * sufflen);
	prefix = malloc(sizeof(char) * length + 1);
	strncpy(suffix, Node->string + length, sufflen);
	strncpy(prefix, Node->string, length);
	prefix[length] = '\0';
	Node->string = prefix;
	RadixPtr SuffixNode = RadNodeCreate(suffix, strlen(suffix));
	SuffixNode->Child = Node->Child;
	SuffixNode->Index = Node->Index;
	SuffixNode->Parent = Node;
	Node->Child = SuffixNode;
	Node->Index = NULL;
	Node->len = strlen(prefix);
	

}

void Find(RadixPtr Head, RadixPtr C, char* token, const char* path) {

	int toklen = (int) strlen(token);
	SortedListPtr *Result;
	cmptype compare = &CompareBucket;
	deltype delete = &SLBucketDestroy;
	IndexPtr newIndex;
	if (C == NULL) {
		Result = InsertToken(Head, token);

		if (*Result == NULL) {

			(*Result) = (SLCreate(compare, delete));
			if ((*Result) == NULL) {
				printf("Failed to Create Bucket \n");
				return;
			}

		}

		newIndex = IndexNodeCreate(path);
		SLInsert(*Result, newIndex);
		return;
	}

	int prelen = PrefixFinder(C->string, token, C->len, toklen);

	if (prelen == 0) {

		Find(Head, C->Next, token, path);
		return;
	}

	else if (prelen < toklen) {

		char* newtok = malloc(sizeof(char) * (toklen - prelen + 1));
		strncpy(newtok, token + prelen, toklen - prelen);
		newtok[strlen(newtok)] = '\0';
		if (prelen < C->len) {
			NodeCutter(C, prelen);

		}
		//	Head = C;
		//	C = C->Child;

		Find(C, C->Child, newtok, path);
		return;

	}
	Result = InsertToken(Head, token);
	if (*Result == NULL) {
		(*Result) = (SLCreate(compare, delete));
		if ((*Result) == NULL) {
			printf("Failed to Create Bucket \n");
			return;
		}
	}

	newIndex = IndexNodeCreate(path);
	SLInsert(*Result, newIndex);
	return;

}

void PreorderTraverse(RadixPtr Head, char* token, SortedListPtr Output,
		StructFiller sF) {

	char* fullstr;
	if (Head == NULL) {
		return;
	}

	if (Head->len == 0) {

		return;
	}
	fullstr = malloc(sizeof(char) * (1 + strlen(Head->string) + strlen(token)));
	fullstr[0] = '\0';
	strcat(fullstr, token);
	strcat(fullstr, Head->string);
	fullstr[(strlen(Head->string)) + strlen(token)] = '\0';
	if (Head->Index != NULL) {

		SLInsert(Output, sF(fullstr, Head->Index));
	}
	if (Head->Child != NULL) {

		PreorderTraverse(Head->Child, fullstr, Output, sF);

	}

	if (Head->Next != NULL) {

		PreorderTraverse(Head->Next, token, Output, sF);
	
	}

	
	return;

}
