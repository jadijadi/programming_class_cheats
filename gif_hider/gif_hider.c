#include <stdio.h>
#include <string.h>

#define MAX_FILE_SIZE (1024*1024)

int to_decimal(char* str)
{
    int decimal;
    for (int i=0; i<strlen(str); i++)
        decimal += str[i]-'0';
    return decimal;
}

int main(int argc, char *argv[])
{
    if(argc == 3 || argc == 4) {
        FILE *fptr;
        char data[MAX_FILE_SIZE];
        char* export_path;

        if (argc == 3)
            export_path = "./coded_file.code";
        else
            export_path = argv[3];

        fptr = fopen(argv[2], "rb");

        int i = 0;
        while (!feof(fptr))
            data[i++] = fgetc(fptr);
        fclose(fptr);

        fptr = fopen(export_path, "wb");

        int code_key = to_decimal(argv[1]);

        for (int j=0; j<i-1; j++)
            fputc((data[j] ^ code_key), fptr);
        fclose(fptr);
    }

    return 0;
}
