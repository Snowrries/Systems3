/*
 * tokenizer.c
 */


void matching(const char *fds){	
	regex_t patmat;/*Pattern matching*/
	regmatch_t matmat;/*matchmat*/
	FILE *b;
	char ** desu;
	size_t * bufflen;
	char *ofst;/*Offset*/
	
	char *inst; /*Insert value in burlapSack*/
	bufflen* = 30;
	desu = malloc()(bufflen*) * sizeof(char*));
	
	b = fopen(fds,"r");
	while(getline(desu, bufflen, b) > 0){
				/*regex me?*/
				if(regcomp(&patmat,REGEXPAT,REG_ICASE)!=0){
					printf("ERROR, ERROR. Fix me please. And hurry up about it.");
				}
				ofst = (char *)malloc((1+strlen(b))*sizeof(char *));
				if(regexec(&patmat, b, 1+strlen(b), matmat, 0)==0){
						/*It matched~!*/
						/*Here, we put the matches in the data struct. */
						while(rm_so!=NULL){
							inst = malloc((rm_eo - rm_so)*sizeof(char));
							inst = b + rm_so;
							/*Call the insert function!*/
							InsertToken(RadNodeCreate(inst, strnlen(inst,em_eo)));
						}
						/*End loop, line has been processed. */
					}
				/*Free reg for use in next line desu. 
				Maybe we can move regcomp out of the loop and free it later?)*/
		regfree(&patmat);/*I reaaaaaaaaaaaally hope this line's right. If it's broke, check here at some point.*/
		fclose(b);
		free(desu);
}
