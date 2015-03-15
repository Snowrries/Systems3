#include "tokenizer.h"


TokenizerT *TKCreate(const char * filename ) {
	char *desu;
	size_t bufflen;
	int getl;
	TokenizerT *tk = (TokenizerT *)malloc(sizeof(TokenizerT));
	if(tk==NULL){
		return NULL;
	}	
	tk->boo = fopen(filename, "r");
	tk->wholefile = malloc(sizeof(char));
	tk->wholefile[0] = '\0';
	while((getl = getline(&desu, &bufflen, tk->boo)) > 0){
		tk->wholefile = (char*)realloc(tk->wholefile, sizeof(char)*(strlen(tk->wholefile)+strlen(desu)) );
		desu[( (int)strlen(desu))-1] = ' ';
		strcat(tk->wholefile,desu);
	//	printf("%s\n", tk->wholefile);
	}
	
	printf("%s\n", tk->wholefile);
	int regerrorcode = regcomp(&(tk->rx),REGEXPAT, REG_EXTENDED|REG_ICASE);
	if (regerrorcode){
		printf("well regcomp failed so here is the error code %d\n", regerrorcode);
		return NULL;
	}	
	tk->untokened = (char *)malloc((strlen(tk->wholefile)+1) * sizeof(char *));
	strcpy(tk->untokened, tk->wholefile);
	tk->hasNext=regexec(&(tk->rx),tk->untokened, 1, &(tk->matches), 0);

	tk->charsfromleft=(regoff_t)0;
	tk->numtoken=0;
	return tk;



}
void TKDestroy( TokenizerT * tk ) {
	free(tk->untokened);
	fclose(tk->boo);
	regfree(&(tk->rx));
	//regfree(&(tk->keywordrx));
	free(tk);
}
char *TKGetNextToken( TokenizerT * tk ) {
		int i;
		if(tk->hasNext){
			return 0;
		} 
		int numchars=(int) tk->matches.rm_eo - (int)tk->matches.rm_so;
		char *tokenz = (char *)malloc((numchars+1) * sizeof(char));
		strncpy(tokenz, tk->untokened+tk->matches.rm_so+tk->charsfromleft, numchars);
		tokenz[numchars]='\0';
//		printf("%s",tokenz);
		regoff_t tempCharsholder = tk->matches.rm_eo;
		tk->hasNext = regexec(&tk->rx,tk->untokened+tk->matches.rm_eo+tk->charsfromleft, 1, &tk->matches, REG_NOTBOL);
		tk->charsfromleft+=tempCharsholder;
		char *done = (char *)malloc((strlen(tokenz)+1)*sizeof(char)+1);
		sprintf(done,"%s",  tokenz);
	//	printf("%s\n", done);
		free(tokenz);
		i = 0;
		while(done[i]){
			done[i] = tolower(done[i]);
			i++;
		} 
	//	printf("%s\n", done);
//gief root and path TKGetNextToken(stuff,root,path);
		return done;


}
int TKhasNext(TokenizerT * tk){	
	if(tk->hasNext == 0){
		return 1;
	}
	return 0;
}

