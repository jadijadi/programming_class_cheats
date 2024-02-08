#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FILE_SIZE (1024 * 1024)

void usage()
{
	// prints the way to use the program
	printf("usage: gif-hider <command> [key] [filename]\n");
	printf("changes the state of being encoded/decoded\n");
	printf("commands:\n");
	printf("    help\n");
	printf("    encode/decode\n");
}

void error(int argc, char *argv[])
{
	// after checking for possible errors,
	// prints the appropriate error message.
	fprintf(stderr, "\033[31m");
	if (argc == 1)
	// means nothing is givven as
	// an argument in the command line
	{
		fprintf(stderr, "error: no commands provided.\n");
	}
	else if (argc == 2)
	// means only one argument, just help wont produce an error
	{
		if (!(strcmp(argv[1], "encode") &&
			  strcmp(argv[1], "decode")))
			fprintf(stderr, "no key specified\n");
		else if (strcmp(argv[1], "help"))
			fprintf(stderr, "command %s not found\n", argv[1]);
	}
	else
	// two arguments even if other arguments could be used as
	// encode/decode command and a key, there wont be a file to open.
	{
		if (!(strcmp(argv[1], "encode") &&
			  strcmp(argv[1], "decode")))
			fprintf(stderr, "no files specified\n");
		else if (strcmp(argv[1], "help"))
			fprintf(stderr, "command %s not found\n", argv[1]);
	}
	fprintf(stderr, "\033[0m");
	usage();
}

bool check_error(int argc, char *argv[])
{
	if (argc <= 3)
	{
		error(argc, argv);
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	bool errored = check_error(argc, argv);
	if (errored)
	{
		if (argc > 1)
			if (!strcmp(argv[1], "help"))
				return 0;
		return 1;
	}
	int key = atoi(argv[2]);
	if (key == 0)
	{
		if ((strcmp(argv[2], "0")))
		{
			printf("key should be an integer number not %s\n", argv[2]);
			return 1;
		}
	}
	for (int fnumber = 3; fnumber < argc; fnumber++)
	{
		FILE *fptr;
		char *fname = argv[fnumber];
		char data[MAX_FILE_SIZE];

		fptr = fopen(fname, "rb");

		int i = 0;
		while (!feof(fptr))
			data[i++] = fgetc(fptr);
		fclose(fptr);

		fptr = fopen(fname, "wb");

		for (int j = 0; j < i - 1; j++)
			fputc((data[j] ^ key), fptr);
		fclose(fptr);
	}
	return 0;
}
