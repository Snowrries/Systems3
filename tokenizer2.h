/*
 * tokenizer2.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Anthony
 */

#ifndef TOKENIZER2_H_
#define TOKENIZER2_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
struct input{
	int fd;
	char buffer[2048];
	int length;
	int used;
};

typedef struct input* Reader;

/*
 *Create struct Input that can keep track of location in file
 *Input: A Path name
 *Output: None but creates Struct Input
 */
Reader CreateReader(FILE*);
/*
 * Destroys struct Input
 * Input: takes in Reader
 * Output:None, frees struct
 */
void DestroyReader(Reader);

/*Traverses through the File given by Reader and creates tokens
 * Input: Struct Reader which contians file information
 * Output: A valid Alphanumeric token
 */
char* tokenize(Reader);

/*Resets Reader back to the beginning if needed
 * Takes in Reader and a file descriptor
 */
void resetinput(struct input*, int);

/*Returns a char from the file
 * Input:A struct Input* which contains file information
 */
char readinput(struct input*);

#endif /* TOKENIZER2_H_ */
