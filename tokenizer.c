/*
 * tokenizer.c
 */
#include <stdio.h>
#include <regex.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define REGEXPAT "([A-Z]|[a-z]|[0-9])*"


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char* untokened;
	regoff_t charsfromleft;
	int numtoken;
	regmatch_t matches;
	regmatch_t matlol;
	regex_t rx;
	regex_t keywordrx;
	int hasNext;
	int wasModified;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

/*
  It generates 2 regex_t type objects by compiling the string containing the expression regexpat and regexpat2
  is defined above so that it dosn't clutter the code with the pattern
  regex pat contains the regular expression as defined in the pdf while regex2 is used to test if a word is in fact a c keyword,
  because it is a lot easier to write than a bunch of if elses with comparisons 
  in order for hasnext to be intilized, the regex must be ran once to give an output of 0 for success or otherwise a 1 for no match
  so in a sense it will always have the next, if any, token already matched

*/
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

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */
/*
 frees stuff, nuff said
*/
void TKDestroy( TokenizerT * tk ) {
	free(tk->untokened);
	regfree(&(tk->rx));
	regfree(&(tk->keywordrx));
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */
/*
 uses regex.h POSIX to actually get the Start Offset and End Offset of each token, stored in 
 matches.rm_eo and .rm_so, and regex only does it for the first found match.
 since at the start, regex has already found the next token's offsets it just uses them to copy a 
 section of the imput text to another string and then it runs regex again to set it up for next use
 the redoFlag is there incase we get a comment and need to skip that
*/
char *TKGetNextToken( TokenizerT * tk ) {
	int redoFlag;
	do{
		redoFlag=0;
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
		//replace this part for any token you want to skip
		if(strncmp("//", tokenz, 2)== 0||strncmp("/*", tokenz, 2)==0){
			redoFlag=1;
			free(tokenz);
			continue;
		}
		if(*tokenz=='\\'){
			char * ecperror = idEsc(tokenz);
			if(ecperror==NULL){
				fprintf(stderr, "something went wrong with escape\n" );
				abort();
			}
			free(tokenz);
			return ecperror;
		}
		char* tokenType= idToken(tokenz, tk);
		int len = strlen(tokenType);
		char *done = (char *)malloc((len+3+strlen(tokenz))*sizeof(char)+1);
		sprintf(done,"%s \"%s\"", tokenType, tokenz);
		free(tokenz);
		return done;
	}while(redoFlag);
	return 0;


}
int TKhasNext(TokenizerT * tk){	
	if(tk->hasNext == 0){
		return 1;
	}
	return 0;
}

