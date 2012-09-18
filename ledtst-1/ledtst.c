
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

int main(int argc, char **argv) 
{ 	int fd;
	unsigned int a = 1;
	fd = open("/dev/gpb5", O_RDWR); 
	if (fd < 0) 
		printf("Problem Opening\n"); 
	
	ioctl(fd, 0,1);
	usleep(800000);
	ioctl(fd, 0,0);
	//printf("in userspace - %d\n",a);
	//ioctl(fd, 1);
	close(fd); 
	return 0; 
}
