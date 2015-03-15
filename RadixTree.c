


#include "RadixTree.h"

RadixPtr RadNodeCreate(char* str, int length){
	RadixPtr newNode = (RadixPtr) malloc(sizeof(struct RadixNode));
	newNode->string = str;
	newNode->len = length;
	newNode->Child = NULL;
	newNode->Index = NULL;
	newNode->Next = NULL;
	newNode->Parent = NULL;
	return newNode;

}

IndexPtr IndexNodeCreate(const char* path){
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
        printf("Inserttoken: %s\n", token);
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
	Prev->Next = Obj;
	Child = Obj;
	return &(Obj->Index);
}


int CompareNodes(RadixPtr Key,RadixPtr Token){

	if(Token->string == NULL){
		return -1;
	}
	return strcmp(Key->string,Token->string);
}



int CompareBucket(void* K, void* I){
	IndexPtr Key = (IndexPtr) K;
	IndexPtr Insert = (IndexPtr) I;
	int result = strcmp(Key->file,Insert->file);
	if(result == 0){
		Key->freq++;
	}
	return result;
}

void SLBucketDestroy(void* Node){
	IndexPtr Del = (IndexPtr) Node;
	Del->file = NULL;
	free(Del);

}

void TreeDestruct(RadixPtr root){

	if(root == NULL){
			return;
	}
	while(root->Child != NULL){
		TreeDestruct(root->Child);
		root->Child = NULL;
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
	prefix = malloc(sizeof(char) * length+1);
	strncpy(suffix,Node->string + length,sufflen);
	strncpy(prefix,Node->string,length);
	prefix[length] = '\0';
	printf("early prefix: %s\n", prefix);
	printf("Node->string %s\n", Node->string);
	Node->string = prefix;
	RadixPtr SuffixNode = RadNodeCreate(suffix,strlen(suffix));
	SuffixNode->Child = Node->Child;
	SuffixNode->Index = Node->Index;
	SuffixNode->Parent = Node;
	Node->Child = SuffixNode;
	Node->Index = NULL;
	Node->len = strlen(prefix);
//	printf("suffnode: %s\n", SuffixNode->string);
	printf("prelen: %d, nodelen: %d\n", length, Node->len);
        printf("suffix: %s\nprefix: %s\n",suffix,prefix);

	free(suffix);
	free(prefix);
}


void InserttoTree(RadixPtr Head,RadixPtr C,char* token,const char* path){

	int toklen =(int) strlen(token);
	SortedListPtr *Result;
	cmptype compare = &CompareBucket;
	deltype delete = &SLBucketDestroy;
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
//	printf("Headstr: %s, token: %s \n",Head->string, token);
	if(prelen == 0){

		InserttoTree(Head,C->Next,token,path);
		return;
	}

	else if(prelen < toklen){

		char* newtok = malloc(sizeof(char) * (toklen - prelen));
		strncpy(newtok,token+prelen, toklen - prelen );
		token = newtok;
		free(newtok);
		if(prelen < C->len){
			NodeCutter(C,prelen);

		}
	//	Head = C;
	//	C = C->Child;

		InserttoTree(C,C->Child,token,path);
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




void PreorderTraverse(RadixPtr Head,char* token,SortedListPtr Output,StructFiller sF){


	if(Head == NULL){

		return;
	}

	if(Head->len == 0){

		return;
	}
	//char* tmp = strcpy();
	token = realloc(token, sizeof(char) * (1 + strlen(Head->string) + strlen(token)));
	strcat(token,Head->string);

//	int sconeness = sizeof(char)*(strlen(token)+strlen(Head->string)+1);
//	char *scone = malloc(sconeness);
//	strcpy(scone, Head->string);
//	strcat(scone,token);
	if(Head->Index !=NULL){

		SLInsert(Output,sF(token,Head->Index));
		}

	PreorderTraverse(Head->Child,token,Output,sF);
	
	char* newtok = malloc(sizeof(char) *(1+ (strlen(token) - Head->len)));
	newtok[0] = '\0';
	
	strncpy(newtok,token,strlen(token) - Head->len );
	token = newtok;
	printf("head: %s, token: %s, newtok: %s\n", Head->string, token, newtok);
//	token[strlen(token)-1]='\0';
	PreorderTraverse(Head->Next,token,Output,sF);
	free(newtok);
//	free(scone);




}



