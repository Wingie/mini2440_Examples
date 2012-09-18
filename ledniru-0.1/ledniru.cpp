#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *c=fopen("/dev/tty1","w");
	fprintf(c,argv[1]);
	fprintf(c,"\n");
	fclose(c);
	exit(EXIT_SUCCESS);
}
