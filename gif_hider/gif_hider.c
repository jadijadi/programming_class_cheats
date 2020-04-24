#include <stdio.h>

#define MAX_FILE_SIZE (1024*1024)
int main (int argc, char *argv[])
{
	FILE *fptr;
	char data[MAX_FILE_SIZE];

	// fn => file name.
	char *fn = argv[1];

	fptr = fopen(fn, "rb");

	int i = 0;
	while (!feof(fptr))
		data[i++] = fgetc(fptr);
	fclose(fptr);

	fptr = fopen(fn, "wb");

	for (int j=0; j<i-1; j++)
		fputc((data[j] ^ 0x60), fptr);
	fclose(fptr);

	return 0;
}





