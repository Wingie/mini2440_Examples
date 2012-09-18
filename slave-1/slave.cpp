#include <iostream>
#include <string>
#include <string.h>
#include <stdint.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
using namespace std;

void ledn(int l, char s[])
{
	char ld[2];
	char stp[2];
	sprintf(ld,"%d",l);
	char led[25] = "/sys/class/leds/led";
    strcat(led,ld);
    strcat(led,"/brightness");
	FILE *ctr = fopen(led,"w");
	fprintf(ctr,s);
    fclose(ctr);
}

int main(int argc, char* args[]){

	
	string python_message = "";
	bool quit = false;
	setuid(0);
	
	while (!quit)
	{
		cin >> python_message;	
		if (python_message == "quit"){
		quit = true;
		}else if (python_message == "1"){
			ledn(1,"1");	
		}else if (python_message == "2"){
			ledn(1,"0");
		}else {
		cout << "Huh?" << endl;
		}	
	}	
	return 0;
}

