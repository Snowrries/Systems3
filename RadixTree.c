


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
SortedListPtr InsertToken(RadixPtr Head,RadixPtr Obj){
	Obj->Parent = Head;
	RadixPtr Child = Head->Child;
	RadixPtr Prev = Head->Child;
	int cmpresult;
	if(Child == NULL){
		Head->Child = Obj;
		return Obj->Index;
	}

	//Go through the list of Child Nodes of Parent Node Head
	while(Child->Next != NULL){
		cmpresult = CompareNodes(Child,Obj);
		if(cmpresult<0){
				Prev->Next = Obj;
				Obj->Next = Child;
				return Obj->Index;
			}
		//If there is a duplicate no need to insert Node
		else if(cmpresult == 0){

			return Head->Index;
		}
		Prev = Child;
		Child = Child->Next;

	}

	Child->Next = Obj;
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
	if(key == NULL){
		return -1;
	}
	for(i = 0; i < insertlen; i ++){
		insert++;
		key++;
		if(i == keylen || strncmp(key,insert,i) != 0){
			return i;
		}

	}
	return insertlen;
}
/*Splits a Node to a prefix and suffix/ Suffix becomes a child node
 * Input: Node to Split and Length of the Prefix
 * Output: None but cuts the node
 */

void NodeCutter(RadixPtr Node, int length){

	char suffix[10];
	memcpy(suffix,Node->string + length,Node->len - length + 1);
	RadixPtr SuffixNode = RadNodeCreate(suffix,length);
	SuffixNode->Child = Node->Child;
	SuffixNode->Index = Node->Index;
	SuffixNode->Parent = Node;
	Node->Child = NULL;
	Node->Index = NULL;


}
/*Locates the proper location to insert the token; calls Cut accordingly
 *Input: Parent Node, Child Node, token desired to be inputted
 *Output: SortedListPtr Index of File/Freq
 */

SortedListPtr InsertLocator(RadixPtr Head,RadixPtr Child,char* token){
	int toklen =(int) strlen(token);
	RadixPtr tok = RadNodeCreate(token,toklen);

	//Child->HeadPtr = Head;
	int prelen = PrefixFinder(Child->string,token,Child->len,toklen);
	//Its the end of the list
	if(prelen == -1){
		return InsertToken(Head,tok);
	}
	if(prelen == 0){
		return InsertLocator(Head,Child->Next,token);
	}
	else if(prelen < toklen){
		memmove(token,token+prelen, toklen - prelen + 1);
		toklen= toklen - prelen;
		if(prelen < Child->len){
			NodeCutter(Child,prelen);
		}

		Head = Child;
		Child = Child->Child;
		return InsertLocator(Head,Child,token);

	}

	return InsertToken(Head,tok);
}

/*INCOMPLETE
 * Traverses through the tree
 * Input: RootPtr of Tree
 * Output: Some sort of Struct that contains token, file, freq info
 *
 */



void PreorderTraverse(RadixPtr Head){

	//char token[50];
	if(Head->Index !=NULL){
		if(Head->Child != NULL){
		PreorderTraverse(Head->Child);
		}
		else{

			Head = Head->Next;
			PreorderTraverse(Head);
		}
		return;
	}
	if(Head->Child == NULL){
		if(Head->Next == NULL){
			Head = Head->Parent->Next;
			PreorderTraverse(Head);
		}
		Head = Head->Next;
		PreorderTraverse(Head);
	}
	else{
	Head = Head->Child;
	PreorderTraverse(Head);
	}


}
