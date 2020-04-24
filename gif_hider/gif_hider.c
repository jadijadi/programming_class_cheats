#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_SIZE (1024*1024)
#define MAX_FILE_NAME (100)

int main (int argc, char *argv[])
{
	if (argc != 4 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
	{
		printf("Usage: gif_hider OPTIONS CODE FILE\n");
		printf("Hide your .gif files.\n");
		printf("Example: gif_hider -e 70 phpconf.gif\n\n");
		printf("OPTIONS:\n");
		printf("  -e    Encryption\n");
		printf("  -d    Decryption\n");
		printf("CODE the code that file is going to be coded with it.\n");
		printf("FILE the .gif/.cif file name.\n");
		return 0;
	}
	char opt[10];
	strcpy(opt, argv[1]);

	char code = 0;
	code = atoi(argv[2]);

	char fname[MAX_FILE_NAME];
	strcpy(fname, argv[3]);
	
	FILE *fptr;
	char data[MAX_FILE_SIZE];

	fptr = fopen(fname, "rb");

	int i = 0;
	while (!feof(fptr))
		data[i++] = fgetc(fptr);
	fclose(fptr);

	fptr = fopen(fname, "wb");

	for (int j=0; j<i-1; j++)
		fputc((data[j] ^ code), fptr);
	fclose(fptr);

	return 0;
}
