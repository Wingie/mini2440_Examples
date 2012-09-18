#include <stdint.h>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "keys.h"


int main (int argc, char **argv)
{
	int keys, rd, i;
	struct input_event ev[64];

	if ((keys = open("/dev/input/buttons", O_RDONLY)) < 0) {
		perror("cannot open them damn buttons.. :'(");
		return 1;
	}


	while (1) {
		rd = read(keys, ev, sizeof(struct input_event) * 64);

		if (rd < (int) sizeof(struct input_event)) {
			printf("ERROR!!!!!\n");
			perror("\nerror reading event pa.");
			return 1;
		}

		for (i = 0; i < rd / sizeof(struct input_event); i++)
			if(ev[i].type == 1)			
			{
				printf("You've pressed a button with code: %d (%s) and value: %d\n",
					ev[i].code,
					names[ev[i].type][ev[i].code],
					ev[i].value);
			}	

	}
}


