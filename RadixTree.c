


#include "radixtree.h"
/*
 * Initialize a Node for the Radix Tree
 * Input: A char* Token String and Length of Token
 *
 * string: Contains Prefix Str
 * len: Contains len of Prefix Str
 * Child: Contains Pointer to Child of Node
 * Index: SortedListPtr Contains File/Freq Information/ Cannot be used in Tree
 * Next: Contains Pointer to Next Node
 * Parent: Contains Pointer to Parent Node
 *
 *
 * Output: A RadixNode
 */
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

/*
 * Constructs a RadixTreePtr
 * Input: None
 * Output: RootPtr of RadixTree
 */

RadixPtr MakeLikeATree(){
	RadixPtr headptr = RadNodeCreate(" ",0);
	return headptr;
}

/*Inserts the token into the Tree
 *Input: Node of Parent Node and Child Node desired to insert
 *Output: Returns a SortedListPtr which contains information for File/Freq
 */
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
/*Compares two Keys contained two Nodes; Used for Sorting
 * Input: Two Tree Nodes
 * Output: if Key>Token return >0 , Key<Token return <0, Equal return 0
 */

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
/*
 * Destroys the Tree
 * Input: Root Ptr of Tree
 * Output: None
 */
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
/*
		**Incomplete**
	Prints tree alphabetically.
	Input: Root ptr of tree
	Output: A text file containing a formatted list of the
	tree data in alphabetical sorted order.
*/
	FILE* TreePrint(RadixPtr root, FILE* f){
		char* ditto;
		int buflen;
		buflen = 99;
		
		fopen(f, "w");
		csnprintf(ditto, buflen, "{%s : [\n", (char*)f);
		fwrite(ditto,1,strlen(ditto)); //Maybe gubby? 
	while(root->Next!=NULL){
		while(root->Child != NULL){
			fwrite("\t{%s : [\n", root->string);
			fwrite("\t\t{%s : %d}\n", root->Index->file, root->Index->occ); // Change what these are called to fit the Index
			TreePrint(root->Child);
		}
		TreePrint(root->Next);
	}
	fwrite("\t\t]}");
		fwrite("\t]}");
		
		return f;
	}
	
/*Compares Two Strings and Finds Length of the matching prefix
 * Input: String to Compare to, String desired to be inserted, Length of Key, Length of insertstring
 * Output: Length of matching prefix characters
 */

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
/*Splits a Node to a prefix and suffix/ Suffix becomes a child node
 * Input: Node to Split and Length of the Prefix
 * Output: None but cuts the node
 */

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
/*Locates the proper location to insert the token; calls Cut accordingly
 *Input: Parent Node, Child Node, token desired to be inputted
 *Output: SortedListPtr Index of File/Freq
 */

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

/*Complete
 * Traverses through the tree
 * Input: RootPtr of Tree
 * Output: Some sort of Struct that contains token, file, freq info
 *
 */

//void PreorderTraverse(RadixPtr Head,SortedListPtr Indexes,StructFiller sF,char* token){

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



