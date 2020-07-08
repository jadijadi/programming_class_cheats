#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FILE_SIZE (1024*1024)
#define MAX_SECRET_KEY 0xFF

bool handleError(unsigned char secretKey);

int main (int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("\tsyntax wrong!");
        return 0;
    }

    char* filename = argv[1];
    unsigned char secretKey = strtol(argv[2], NULL, 0);

    if (handleError(secretKey))
        return 0;

	FILE *fptr;
	char data[MAX_FILE_SIZE];

    // Read from File
	fptr = fopen(filename, "rb");
    if (!fptr)
    {
        printf("\tinput file invalid!\n");
        return 0;
    }

	int i = 0;
	while (!feof(fptr))
		data[i++] = fgetc(fptr);
	fclose(fptr);
    // !Read from File

    // Write to File
	fptr = fopen(filename, "wb");
	for (int j=0; j<i-1; j++)
		fputc((data[j] ^ secretKey), fptr);
	fclose(fptr);
    // !Write to File

    printf("file \"%s\" encrypted/decrypted with \"0x%X\" secret key.\n", filename, secretKey);
	return 0;
}

bool handleError(unsigned char secretKey)
{
    char* error = "";
    if (!secretKey)
        error = "0 secret key does not affect\n";
    else if (secretKey > MAX_SECRET_KEY)
        error = "\tsecret key is large!\n";

    if (error != "")
    {
        printf("%s", error);
        return true;
    }
    return false;
}
