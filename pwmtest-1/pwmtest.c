#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/select.h> 
#include <sys/time.h> 
#include <string.h>

int main(int argc, char *argv[])
{
	printf("Hello World, I'm pwmtest!\n");
	int fd;
	unsigned int a = 155;
	fd = open("/dev/pwm0", O_RDWR); 
	if (fd < 0) 
		printf("Problem Opening\n"); 
	ioctl(fd, 0,&a);
	
	exit(EXIT_SUCCESS);
}
