
 /* tokenizer.c
 *
*/
#include "tokenizer.h"

TokenizerT *TKCreate( char * ts ) {
	TokenizerT *tk = (TokenizerT *)malloc(sizeof(TokenizerT));
	if(tk==NULL){
		return NULL;
	}	
	tk->untokened = (char *)malloc((strlen(ts)+1) * sizeof(char *));
	strcpy(tk->untokened, ts);
	tk->hasNext=regexec(&(tk->rx),tk->untokened, 1, &(tk->matches), 0);

	tk->charsfromleft=(regoff_t)0;
	tk->numtoken=0;
	

  return tk;
}

void TKDestroy( TokenizerT * tk ) {
	free(tk->untokened);
	regfree(&(tk->rx));
	regfree(&(tk->keywordrx));
	free(tk);
}
char *TKGetNextToken( TokenizerT * tk ) {
		if(tk->hasNext){
			return 0;
		} 
		int numchars=(int) tk->matches.rm_eo - (int)tk->matches.rm_so;
		char *tokenz = (char *)malloc((numchars+1) * sizeof(char));
		strncpy(tokenz, tk->untokened+tk->matches.rm_so+tk->charsfromleft, numchars);
		tokenz[numchars]='\0';
		regoff_t tempCharsholder = tk->matches.rm_eo;
		tk->hasNext = regexec(&tk->rx,tk->untokened+tk->matches.rm_eo+tk->charsfromleft, 1, &tk->matches,REG_NOTBOL);
		tk->charsfromleft+=tempCharsholder;
		char *done = (char *)malloc((strlen(tokenz)+1)*sizeof(char)+1);
		sprintf(done,"%s",  tokenz);
		free(tokenz);
		return done;


}
/* 
void matching(const char *fds){	
	regex_t patmat;////Pattern matching////
	regmatch_t matmat;////matchmat////
	regoff_t start;
	regoff_t end;
	
	FILE *b;
	char * desu;
	size_t bufflen;
	char *ofst;////Offset////
	
	char *inst; ////Insert value in burlapSack////
	
	bufflen = 30;
	desu = malloc((*bufflen) * sizeof(char));
	
	b = fopen(fds,"r");
	while(getline(&desu, &bufflen, b) > 0){
		
				if(regcomp(&patmat,REGEXPAT,REG_ICASE)!=0){
					printf("ERROR, ERROR. Fix me please. And hurry up about it.");
				}
				
				ofst = (char *) malloc((1+(int)strlen(desu))*sizeof(char ));
				if(regexec(&patmat, desu, 1+strlen(desu), &matmat, 0)==0){
						////It matched~!////
						////Here, we put the matches in the data struct. ////
					//Comparison Between pointer and integer
					//rm_so by itself is undefined
					
						while(matmat.rm_so!=NULL){
							inst = malloc((matmat.rm_eo - matmat.rm_so)*sizeof(char));
							inst = b + matmat.rm_so;
							////Call the insert function!////
							//NO YOU DON'T CALL INSERTTOKEN
							//INSERTLOCATOR IS THE ONE TO USE

							//InsertToken(RadNodeCreate(inst, strnlen(inst,matmat.rm_eo)));
						//}
						////End loop, line has been processed. ////
					//}
				Free reg for use in next line desu. 
				Maybe we can move regcomp out of the loop and free it later?)////
		regfree(&patmat);
		fclose(b);
		free(desu);
} */


