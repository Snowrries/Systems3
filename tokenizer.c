/*
 * tokenizer.c
 */
/*
#include "tokenizer.h"
void matching(const char *fds){	
	regex_t patmat;/*Pattern matching*/
//	regmatch_t matmat;/*matchmat*/
	/*
	FILE *b;
	char ** desu;
	size_t * bufflen;
	char *ofst;/*Offset*/
	/*
	char *inst; /*Insert value in burlapSack*/
	/*
	*bufflen = 30;
	desu = malloc((*bufflen) * sizeof(char*));
	
	b = fopen(fds,"r");
	while(getline(desu, bufflen, b) > 0){
				/*regex me?*/
	/*
				if(regcomp(&patmat,REGEXPAT,REG_ICASE)!=0){
					printf("ERROR, ERROR. Fix me please. And hurry up about it.");
				}
				//Passing Argument 1 of strlen incompatible pointer type
				ofst = (char *) malloc((1+strlen(b))*sizeof(char ));
				//Passing Argument 2 of strlen incompatible pointer type
				//Incompatible type Argument 4 of regexec
				if(regexec(&patmat, b, 1+strlen(b), matmat, 0)==0){
						/*It matched~!*/
						/*Here, we put the matches in the data struct. */
					//Comparison Between pointer and integer
					//rm_so by itself is undefined
					/*
						while(matmat.rm_so!=NULL){
							inst = malloc((matmat.rm_eo - matmat.rm_so)*sizeof(char));
							inst = b + matmat.rm_so;
							/*Call the insert function!*/
							//NO YOU DON'T CALL INSERTTOKEN
							//INSERTLOCATOR IS THE ONE TO USE

							//InsertToken(RadNodeCreate(inst, strnlen(inst,matmat.rm_eo)));
						//}
						/*End loop, line has been processed. */
					//}
				/*Free reg for use in next line desu. 
				Maybe we can move regcomp out of the loop and free it later?)*/
		/*regfree(&patmat);/*I reaaaaaaaaaaaally hope this line's right. If it's broke, check here at some point.*/
	/*	fclose(b);
		free(desu);
}
*/

