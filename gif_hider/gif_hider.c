#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_SIZE (1024*1024)
#define MAX_FILE_NAME (100)

int main (int argc, char *argv[])
{
	char code = 0;
	code = atoi(argv[1]);

	char fname[MAX_FILE_NAME];
	strcpy(fname, argv[2]);
	
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
