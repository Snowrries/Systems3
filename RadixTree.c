


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
	newNode->Parent=NULL;
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
SortedListPtr InsertToken(RadixPtr Head,char* token){
	RadixPtr Obj = RadNodeCreate(token,strlen(token));
	Obj->Parent = Head;

	RadixPtr Child = (Head->Child);
	RadixPtr Prev = (Head);

	int cmpresult;
	if(Child == NULL){
		Head->Child = Obj;

		return Obj->Index;
	}

	//Go through the list of Child Nodes of Parent Node Head
	while(Child != NULL){

		cmpresult = CompareNodes(Child,Obj);

		if(cmpresult>0){

			if(Prev == Head){
				Obj->Next = Child;
				(Prev)->Child = Obj;
				return Obj->Index;

			}
				Obj->Next = Child;
				(Prev)->Next = Obj;

				return Obj->Index;
			}
		//If there is a duplicate no need to insert Node
		else if(cmpresult == 0){

			return Head->Index;
		}
		Prev = Child;
		Child = (Child)->Next;

	}

	Child = Obj;
	return Obj->Index;
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
/*
 * Destroys the Tree
 * Input: Root Ptr of Tree
 * Output: None
 */
void TreeDestruct(){

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


}
/*Locates the proper location to insert the token; calls Cut accordingly
 *Input: Parent Node, Child Node, token desired to be inputted
 *Output: SortedListPtr Index of File/Freq
 */

void InsertLocator(RadixPtr Head,RadixPtr C,char* token){
	int toklen =(int) strlen(token);


	if(C == NULL){

		 InsertToken(Head,token);
		 return;
	}

	int prelen = PrefixFinder(C->string,token,C->len,toklen);

	if(prelen == 0){

		return InsertLocator(Head,C->Next,token);
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

		InsertLocator(Head,C,token);
		 return;

	}
	InsertToken(Head,token);

	return;
}

/*Complete
 * Traverses through the tree
 * Input: RootPtr of Tree
 * Output: Some sort of Struct that contains token, file, freq info
 *
 */



void PreorderTraverse(RadixPtr Head,SortedListPtr Indexes,StructFiller sF,char* token){


	if(Head == NULL){
		return;
	}
	if(Head->Child == NULL){
		strncpy(token,token,strlen(token) - Head->len +1);
		if(Head->Next == NULL){
			Head = Head->Parent->Next;
			PreorderTraverse(Head,Indexes,sF,token);
		}
		Head = Head->Next;
		PreorderTraverse(Head,Indexes,sF,token);
	}

	strcat(token,Head->string);
	if(Head->Index !=NULL){
		SLInsert(Indexes,sF(Head->Index,token));

		if(Head->Child != NULL){
		PreorderTraverse(Head->Child,Indexes,sF,token);
		}
		else{
			strncpy(token,token,strlen(token) - Head->len +1);
			Head = Head->Next;
			PreorderTraverse(Head,Indexes,sF,token);
		}

	}

	else{
	Head = Head->Child;
	PreorderTraverse(Head,Indexes,sF,token);
	}


}



