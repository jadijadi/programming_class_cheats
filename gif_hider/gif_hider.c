#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#define error_handler(msg)		\
	do { perror(msg); exit(EXIT_FAILURE); } while(0)

char *program_name;

void print_usage(FILE*, int);
void encrypt(const char *, const char *, int);

int main (int argc, char *argv[])
{

	int next_option;
	int code = 1;

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
	
	program_name = argv[0];

	do {
		/* checking given arguments */
		next_option = getopt_long(argc, argv,
				short_options, long_options, NULL);
		switch(next_option){
			case 'h':
				print_usage(stdout, 0);
				break;
			case 'i':
				input_file = (char *)malloc(strlen(optarg));
				if (input_file == NULL)
					error_handler("input filename");
				memmove(input_file, optarg, strlen(optarg));
				break;
			case 'o':
				output_file = (char *)malloc(strlen(optarg));
				if (output_file == NULL){
					error_handler("output filename");
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

void encrypt(const char *input_file, const char *output_file, int code)
{

	/* XXXXXX will be replace with random things by mkstemp */
	char tmp_path[] = ".gif_hider.XXXXXX"; // unique filename avoids overwriting
	FILE *fptro;
	FILE *fptrt;
	int tmpfd;
	char data;

	fptro = fopen(input_file, "rb");

	/* creates and open a file a with unique filename */
	tmpfd = mkstemp(tmp_path);	// returns a file descriptor
	fptrt = fdopen(tmpfd, "wb");	// returns FILE * by given file descriptor

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
	rename(tmp_path, output_file);

}
