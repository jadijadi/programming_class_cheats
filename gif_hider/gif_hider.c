#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

char *program_name;

void print_usage(FILE*, int);
void encrypt(const char *, const char *, long int);

int main (int argc, char *argv[])
{
	program_name = argv[0];

	int next_option;
	long int code = 1;
	const char *short_options = "hi:o:x:";

	const struct option long_options[] = {
		{ "help",   no_argument,	0,   'h'},
		{ "input",  required_argument,	0,   'i'},
		{ "output", required_argument,  0,   'o'},
		{ "hex",    required_argument,  0,   'x'},
		{ NULL,        0,		NULL, 0 }
	};

	char *input_file = NULL;
	char *output_file = NULL;

	do {
		next_option = getopt_long(argc, argv,
				short_options, long_options, NULL);
		switch(next_option){
			case 'h':
				print_usage(stdout, 0);
				break;
			case 'i':
				input_file = (char *)malloc(strlen(optarg));
				if (input_file == NULL){
					perror("memory");
					exit(EXIT_FAILURE);
				}
				memmove(input_file, optarg, strlen(optarg));
				break;
			case 'o':
				output_file = (char *)malloc(strlen(optarg));
				if (output_file == NULL){
					perror("memory");
					exit(EXIT_FAILURE);
				}
				memmove(output_file, optarg, strlen(optarg));
				break;
			case 'x':
				code = (int)strtol(optarg, NULL, 16);
				break;
			case '?':
				print_usage(stderr, 1);
				break;
		}
	} while (next_option != -1);

	if (input_file && output_file){
		encrypt(input_file, output_file, code);
		printf("done whit key: %p\n", code);
	}
	
	free(input_file);
	free(output_file);

	return 0;
}
void print_usage(FILE *stream, int exit_code)
{
	fprintf(stream,
			"\n"
			"Usage: %s [OPTION] [ARGUMENTS]\n"
			"-h  --help		print this menue\n"
			"-i  --inputfile	input file  (to read from)\n"
			"-o  --outputfile	output file (to write to)\n"
			"-x  --hex		hexadecimal key for encryption\n\n",
			program_name);

	exit(exit_code);
}

void encrypt(const char *input_file, const char *output_file, long int code)
{

	FILE *fptro;
	FILE *fptrt;
	char data;

	fptro = fopen(input_file, "rb");
	fptrt = fopen(".tmp.gif", "wb");

	if (!fptro || !fptrt){
		fprintf(stderr, "Error to opening files\n");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (!feof(fptro)){
		data = fgetc(fptro);
		fputc((data ^ code), fptrt);
	}

	fclose(fptro);
	fclose(fptrt);
	
	remove(input_file);
	rename(".tmp.gif", output_file);

}
