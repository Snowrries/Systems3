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

	}
	
	printf("%s\n", tk->wholefile);
	int regerrorcode = regcomp(&(tk->rx),REGEXPAT, REG_EXTENDED|REG_ICASE);
	if (regerrorcode){
		printf("Regex failed with error code: %d\n", regerrorcode);
		return NULL;
	}	
	tk->untokened = (char *)malloc((strlen(tk->wholefile)+1) * sizeof(char *));
	strcpy(tk->untokened, tk->wholefile);
	tk->hasNext=regexec(&(tk->rx),tk->untokened, 1, &(tk->matches), 0);

	tk->charsfromleft=(regoff_t)0;
	tk->numtoken=0;
	return tk;



}

//char text_chars[256] = {
//        /*                  BEL BS HT LF    FF CR    */
//        Fii, Fii, Fii, Fii, Fii, Fii, Fii, Tii, Tii, Tii, Tii, Fii, Tii, Tii, Fii, Fii,  /* 0x0X */
//        /*                              ESC          */
//        Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Tii, Fii, Fii, Fii, Fii,  /* 0x1X */
//        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x2X */
//        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x3X */
//        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x4X */
//        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x5X */
//        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x6X */
//        Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Fii,  /* 0x7X */
//        /*            NEL                            */
//        Xii, Xii, Xii, Xii, Xii, Tii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii,  /* 0x8X */
//        Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii,  /* 0x9X */
//        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xaX */
//        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xbX */
//        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xcX */
//        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xdX */
//        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xeX */
//        Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii   /* 0xfX */
//};
//int
//looksascii(TokenizerT * mememe)
//{       int i;
//        for (i = 0; i < strlen(mememe->wholefile); i++ ) {
//                int t = text_chars[(int)(mememe->wholefile[i])];
//                if (t != Tii) {
//                        return 0;
//                }
//        }
//        return 1;
//}
///*returns 1 if the file is ascii, 0 if not, errno if error.*/
//
//
//

void TKDestroy( TokenizerT * tk ) {
	free(tk->untokened);
	free(tk->wholefile);
	fclose(tk->boo);
	regfree(&(tk->rx));
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
		regoff_t tempCharsholder = tk->matches.rm_eo;
		tk->hasNext = regexec(&tk->rx,tk->untokened+tk->matches.rm_eo+tk->charsfromleft, 1, &tk->matches, REG_NOTBOL);
		tk->charsfromleft+=tempCharsholder;
		char *done = (char *)malloc((strlen(tokenz)+1)*sizeof(char)+1);
		sprintf(done,"%s",  tokenz);
		free(tokenz);
		i = 0;
		while(done[i]){
			done[i] = tolower(done[i]);
			i++;
		}
		return done;


}
int TKhasNext(TokenizerT * tk){	
	if(tk->hasNext == 0){
		return 1;
	}
	return 0;
}

