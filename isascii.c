#include "isascii.h"

char text_chars[256] = {
	/*                  BEL BS HT LF    FF CR    */
	F, F, F, F, F, F, F, T, T, T, T, F, T, T, F, F,  /* 0x0X */
	/*                              ESC          */
	F, F, F, F, F, F, F, F, F, F, F, T, F, F, F, F,  /* 0x1X */
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,  /* 0x2X */
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,  /* 0x3X */
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,  /* 0x4X */
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,  /* 0x5X */
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,  /* 0x6X */
	T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, F,  /* 0x7X */
	/*            NEL                            */
	X, X, X, X, X, T, X, X, X, X, X, X, X, X, X, X,  /* 0x8X */
	X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,  /* 0x9X */
	I, I, I, I, I, I, I, I, I, I, I, I, I, I, I, I,  /* 0xaX */
	I, I, I, I, I, I, I, I, I, I, I, I, I, I, I, I,  /* 0xbX */
	I, I, I, I, I, I, I, I, I, I, I, I, I, I, I, I,  /* 0xcX */
	I, I, I, I, I, I, I, I, I, I, I, I, I, I, I, I,  /* 0xdX */
	I, I, I, I, I, I, I, I, I, I, I, I, I, I, I, I,  /* 0xeX */
	I, I, I, I, I, I, I, I, I, I, I, I, I, I, I, I   /* 0xfX */
};

int
looks_ascii(const unsigned char *buf, size_t nbytes)
{	unsigned int i;
	for ( i = 0; i < nbytes; i++) {
		// buf[i] == (buf+i);
		// buf[i] == 0	
		int t = text_chars[buf[i]];
		if (t != T) {
			return 0;
		}
	}

	return 1;
}
/*returns 1 if the file is ascii, 0 if not, errno if error.*/
int
fakemain(const char **argv)
{
	FILE *fp = 0;

	if ((fp = fopen(argv[1], "rb"))) {
		unsigned char buffer[FR_BUFSIZ] = { 0 };
		size_t nbytes = 0;
		int ascii = 1;
		while (ascii && (nbytes = fread(buffer, sizeof(buffer[0]), FR_BUFSIZ, fp)) > 0) {
			ascii = looks_ascii(buffer, nbytes);
			if (feof(fp)) {
				break;
			}
		};

		if (nbytes == 0) {
			if (ferror(fp)) { /* some sort of error occured */
				fprintf(stderr, "Failed to read file\n");
				ascii = 0;
			} else {
				fprintf(stderr, "Oh god how did you get here?!\n");
				ascii = 0;
			}
		}
		return ascii;
		//printf("%s\n", ascii ? "ascii" : "not ascii");

	} else {
		fprintf(stderr, "Failed to open file: %s\n", strerror(errno));
		return errno;
	}

	if (fp != 0 && fclose(fp) && errno != 0) {
		fprintf(stderr, "Failed to close file: %s\n", strerror(errno));
		return errno;
	}

}
