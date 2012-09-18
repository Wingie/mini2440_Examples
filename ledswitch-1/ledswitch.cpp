#include <stdint.h>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * 59 - led1
 * 60 - led2
 * 61 - led3
 * 64 - led4
 */ 

void ledn(int l, int s)
{
	char ld[3],st[2];
	sprintf(ld,"%d",l);
	sprintf(st,"%d",s);
	//printf(":%s:\n",st);
	char led[25] = "/sys/class/leds/led";
    strcat(led,ld);
    strcat(led,"/brightness");
    //printf("%s\n",led);
	FILE *ctr = fopen(led,"w");
	fprintf(ctr,st);
    fclose(ctr);
}

int main (int argc, char **argv)
{
	int keys, rd, i,l2=0,l3=0;
	unsigned long cnt=0;
	struct input_event ev[64];
	bool k3,k4;
	if ((keys = open("/dev/input/buttons", O_RDONLY)) < 0) {
		perror("cannot open them damn buttons.. :'(");
		return 1;
	} 
	
	/**while(1)
	{
		ledn(1,1);
		usleep(50000);
		ledn(1,0);
		usleep(50000);
	}**/
	//printf("BLah!\n");
	
	
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
				printf("**%d - %d\n",ev[i].code,ev[i].value);
				switch(ev[i].code)
				{
						case 59:
							ledn(1,ev[i].value);
						break;
						case 60:
							if(ev[i].value == 1)
							{
								l2 = (l2==0)?1:0;
								//printf("led2:%d\n",l2);
								ledn(2,l2);
							}
						break;
						case 61:
							k3 = (ev[i].value==1)?true:false;
						break;
						case 64:
							k4 = (ev[i].value==1)?true:false;
						break;
						
				}
				
				if(k3==true&&k4==true)
				{
					ledn(3,1);
					ledn(4,1);
				}
				else
				{
					ledn(3,0);
					ledn(4,0);
				}
			}	

	}
}


