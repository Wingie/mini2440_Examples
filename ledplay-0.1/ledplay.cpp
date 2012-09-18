#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char **argv)
{
	char led[25] = "/sys/class/leds/led";
    strcat(led,argv[1]);
    strcat(led,"/brightness");
    printf("%s\n",led);
	FILE *ctr = fopen(led,"w");
	fprintf(ctr,argv[2]);
    fclose(ctr);
}


