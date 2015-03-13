#ifndef ISASCII_H
#define ISASCII_H
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>  /* for errno */
#include <string.h> /* for strerror */
/* Borrowed from ascmagic.c in the file source tree */
#define F 0   /* character never appears in text */
#define T 1   /* character appears in plain ASCII text */
#define I 2   /* character appears in ISO-8859 text */
#define X 3   /* character appears in non-ISO extended ASCII (Mac, IBM PC) */
#define FR_BUFSIZ 4096

typedef unsigned long unichar;

/*returns 1 if the file is ascii, 0 if not, errno if error.*/
int fakemain(char **argv);

/*	checks every byte in the file against the hardcoded 
	char array and returns 0 if a non-ascii char is found.
	*/
int looks_ascii(const unsigned char *buf, size_t nbytes);


#endif