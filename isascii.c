#include "isascii.h"

char text_chars[256] = {
	/*                  BEL BS HT LF    FF CR    */
	Fii, Fii, Fii, Fii, Fii, Fii, Fii, Tii, Tii, Tii, Tii, Fii, Tii, Tii, Fii, Fii,  /* 0x0X */
	/*                              ESC          */
	Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Fii, Tii, Fii, Fii, Fii, Fii,  /* 0x1X */
	Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x2X */
	Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x3X */
	Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x4X */
	Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x5X */
	Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii,  /* 0x6X */
	Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Tii, Fii,  /* 0x7X */
	/*            NEL                            */
	Xii, Xii, Xii, Xii, Xii, Tii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii,  /* 0x8X */
	Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii, Xii,  /* 0x9X */
	Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xaX */
	Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xbX */
	Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xcX */
	Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xdX */
	Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii,  /* 0xeX */
	Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii, Iii   /* 0xfX */
};

int
looks_ascii(const unsigned char *buf, size_t nbytes)
{	unsigned int i;
	for ( i = 0; i < nbytes; i++) {
		// buf[i] == (buf+i);
		// buf[i] == 0	
		int t = text_chars[buf[i]];
		if (t != Tii) {
			return 0;
		}
	}

	return 1;
}
/*returns 1 if the file is ascii, 0 if not, errno if error.*/
int
fakemain(const char *arv)
{
	FILE *fp;

	if ((fp = fopen(arv, "r"))) {
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

