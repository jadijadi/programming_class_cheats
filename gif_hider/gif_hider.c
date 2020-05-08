#include <stdio.h>
#include <stdlib.h>

int main ()
{
	FILE *fptro;
	FILE *fptrt;
	char data;

	fptro = fopen("phpconf.gif", "rb");
	fptrt = fopen(".phpconf.gif", "wb");

	if (!fptro || !fptrt){
		fprintf(stderr, "Error to opening files\n");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (!feof(fptro)){
		data = fgetc(fptro);
		fputc((data ^ 0x60), fptrt);
	}

	fclose(fptro);
	fclose(fptrt);
	
	remove("phpconf.gif");
	rename(".phpconf.gif", "phpconf.gif");

	return 0;
}
