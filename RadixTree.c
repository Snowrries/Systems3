


#include "radixtree.h"

RadixPtr RadNodeCreate(char* str, int length){
	RadixPtr newNode = (RadixPtr) malloc(sizeof(struct RadixNode));
	newNode->string = malloc(sizeof(char) * length);
	newNode->string = str;
	newNode->len = length;
	newNode->Child = NULL;
	newNode->Index = NULL;
	newNode->Next = NULL;
	newNode->Parent = NULL;
	return newNode;

}

IndexPtr IndexNodeCreate(char* path){
	IndexPtr newNode = (IndexPtr) malloc(sizeof(struct Index));
	newNode->file = path;
	newNode->freq = 1;
	return newNode;

}



RadixPtr MakeLikeATree(){
	RadixPtr headptr = RadNodeCreate(" ",0);
	return headptr;
}


SortedListPtr *InsertToken(RadixPtr Head,char* token){
	RadixPtr Obj = RadNodeCreate(token,strlen(token));
	Obj->Parent = Head;

	RadixPtr Child = (Head->Child);
	RadixPtr Prev = (Head);

	int cmpresult;
	if(Child == NULL){
		Head->Child = Obj;

		return &(Obj->Index);
	}

	//Go through the list of Child Nodes of Parent Node Head
	while(Child != NULL){

		cmpresult = CompareNodes(Child,Obj);

		if(cmpresult>0){

			if(Prev == Head){
				Obj->Next = Child;
				(Prev)->Child = Obj;
				return &(Obj->Index);

			}
				Obj->Next = Child;
				(Prev)->Next = Obj;

				return &(Obj->Index);
			}
		//If there is a duplicate no need to insert Node
		else if(cmpresult == 0){

			return &(Head->Index);
		}
		Prev = Child;
		Child = (Child)->Next;

	}

	Child = Obj;
	return &(Obj->Index);
}


int CompareNodes(RadixPtr Key,RadixPtr Token){

	if(Token->string == NULL){
		return -1;
	}
	return strcmp(Key->string,Token->string);
}



int CompareIndex(void* K, void* I){
	IndexPtr Key = (IndexPtr) K;
	IndexPtr Insert = (IndexPtr) I;
	int result = strcmp(Key->file,Insert->file);
	if(result == 0){
		Key->freq++;
	}
	return result;
}

void SLIndexDestruct(void* Node){
	IndexPtr Del = (IndexPtr) Node;
	Del->file = NULL;
	free(Del);

}

void TreeDestruct(RadixPtr root){
	SortedListIteratorPtr popo;
	SortedListIteratorPtr nana;
	if(root == NULL){
			return;
	}
	while(root->Child != NULL){
		TreeDestruct(root->Child);

	}
	while(root->Next!=NULL){
		TreeDestruct(root->Next);
		root->Next = NULL;
	}
	SLDestroy(root->Index);
	free(root);
	return;
}


int PrefixFinder(char * key,char* insert,int keylen,int insertlen){
	int i;

	for(i = 0; i < insertlen; i ++){
		if(i == keylen || strncmp(key,insert,1) != 0){

			return i;
		}
		key++;
		insert++;

	}
	return insertlen;
}


void NodeCutter(RadixPtr Node, int length){


	int sufflen = Node->len - length + 1;
	char* suffix;
	char* prefix;
	suffix = malloc(sizeof(char) * sufflen);
	prefix = malloc(sizeof(char) * length);

	strncpy(suffix,Node->string + length,sufflen);
	strncpy(prefix,Node->string,length);
	Node->string = prefix;
	RadixPtr SuffixNode = RadNodeCreate(suffix,strlen(suffix));
	SuffixNode->Child = Node->Child;
	SuffixNode->Index = Node->Index;
	SuffixNode->Parent = Node;
	Node->Child = SuffixNode;
	Node->Index = NULL;
	Node->len = strlen(prefix);


}


void InsertLocator(RadixPtr Head,RadixPtr C,char* token,char* path){
	int toklen =(int) strlen(token);
	SortedListPtr *Result;
	cmptype compare = &CompareIndex;
	deltype delete = &SLIndexDestruct;
	IndexPtr newIndex;
	if(C == NULL){
		Result = InsertToken(Head,token);


		 if(*Result == NULL){

			(*Result) = (SLCreate(compare,delete));

		 }
		 newIndex = IndexNodeCreate(path);
		 SLInsert(*Result, newIndex );
		 return;
	}

	int prelen = PrefixFinder(C->string,token,C->len,toklen);

	if(prelen == 0){

		InsertLocator(Head,C->Next,token,path);
		return;
	}

	else if(prelen < toklen){

		char* newtok = malloc(sizeof(char) * (toklen - prelen));
		strncpy(newtok,token+prelen, toklen - prelen );
		token = newtok;

		if(prelen < C->len){
			NodeCutter(C,prelen);

		}
		Head = C;
		C = C->Child;

		InsertLocator(Head,C,token,path);
		 return;

	}
	Result = InsertToken(Head,token);
	 if(*Result == NULL){
		(*Result) = (SLCreate(compare,delete));
	}
	 newIndex = IndexNodeCreate(path);
	 SLInsert(*Result, newIndex );
	  return;

}




void PreorderTraverse(RadixPtr Head,char* token){


	if(Head == NULL){
		printf("Not good");
		return;
	}
	if(Head->len == 0){
		return;
	}

	strcat(token,Head->string);

	/*
	if(Head->Index !=NULL){
	//	SLInsert(Indexes,sF(Head->Index,token));
		printf("So it does");
		printf("%s", token);
		if(Head->Child != NULL){
		//PreorderTraverse(Head->Child,token);
		}
		else{
			strncpy(token,token,strlen(token) - Head->len +1);
			if(Head->Next == NULL){
				Head = Head->Parent->Next;
			//	PreorderTraverse(Head,token);
					}
			Head = Head->Next;
		//	PreorderTraverse(Head,token);
		}

	}
	*/
	if(Head->Child == NULL){
		printf("Ova Here");
		printf("%s",token);
		if(strlen(token) - Head->len == 0){
			token[0] = 0;
		}
		else{
		char* newtok = malloc(sizeof(char) * (strlen(token) - Head->len));
		strncpy(newtok,token,strlen(token) - Head->len );
		token = newtok;
		printf("%s",token);
		}

		if(Head->Next == NULL){
			Head = Head->Parent->Next;

			PreorderTraverse(Head,token);
		}
		Head = Head->Next;

		//printf("%d",Head->Parent->len);
		//printf("%s",Head->Parent->string);
		//PreorderTraverse(Head,token);
	}

	else{
	printf("So it doesn't");
	Head = Head->Child;
	PreorderTraverse(Head,token);
	}


}



