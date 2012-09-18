#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc,char **argv)
{
  const char *output_base;
	const char *video_device;
  int fcount=1;
  int dev_fd;
  int buffer_width;
  int buffer_height;
  int buffer_size;
  int Ysize,CbCrsize;
	struct v4l2_capability cap;
	struct v4l2_format fmt;
	char fourcc[5]={0,0,0,0,0};
	unsigned char **buffers;
  int i;
  struct timeval start;
	struct timeval finish;
	double fps;
	
  if(argc<5)
  {
    fprintf(stderr,"Usage:%s <device> <width> <height> <output_base> [number of frames]\n",argv[0]);
    return 1;
  }
  
	video_device=argv[1];

	memset(&fmt,sizeof(fmt),0);
	fmt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	
	fmt.fmt.pix.width=atoi(argv[2]);
	fmt.fmt.pix.height=atoi(argv[3]);

	
  output_base=argv[4];
  
  if(argc>5) fcount=atoi(argv[5]);

  
  if ((dev_fd = open( video_device, O_RDWR)) == -1)
    perror("ERROR opening camera interface\n");  
  
	if (0 != ioctl(dev_fd, VIDIOC_QUERYCAP, &cap)) {
		if (EINVAL == errno) {
			fprintf (stderr, "%s is no V4L2 device\n",video_device);
			return 1;
		} else {
			perror ("VIDIOC_QUERYCAP");
			return 1;
		}
	}
	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
		fprintf (stderr, "%s is no video capture device\n",video_device);
		return 1;
	}	
	
	if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
		fprintf (stderr, "%s does not support read i/o\n", video_device);
		return 1;
	}	
	
	if (0 != ioctl (dev_fd, VIDIOC_S_FMT, &fmt))
	{
		perror ("VIDIOC_G_FMT");
		return 1;
	}
	
	memmove(fourcc,&fmt.fmt.pix.pixelformat,4);
	
	printf("Goint to capture frames %d x %d format: %4s framesize: %d\n",
				 fmt.fmt.pix.width,
				 fmt.fmt.pix.height,
				 fourcc,
				 fmt.fmt.pix.sizeimage);
								
	
  Ysize=fmt.fmt.pix.width*fmt.fmt.pix.height;
  CbCrsize=fmt.fmt.pix.width*fmt.fmt.pix.height/2;
  buffer_size=fmt.fmt.pix.sizeimage;
  
	buffers=malloc(sizeof(unsigned char *)*fcount);
	
	if(!buffers)
	{
		perror("Can't allocate buffer!\n");
		return 1;
	}
	
	//try to allocate memory for all buffers
	for(i=0;i<fcount;i++)
	{
		if((buffers[i]=malloc(buffer_size))==NULL)
			break;
	}
	
	if(i==0) //didn't allocate any buffer
	{
		perror("Can't allocate single buffer!\n");
		return 1;
	}
	
	fcount=i;
  printf("About to capture %d images to %s\n",fcount,output_base);


	gettimeofday(&start,NULL);
  for(i=0;i<fcount;i++)
  {
    int rd=0;
    
    if((rd=read(dev_fd, buffers[i], buffer_size))<buffer_size)
    {
      fprintf(stderr,"Expected %d got %d!\n",buffer_size,rd);
      continue;
    }
		printf("*");
		fflush(stdout);
	}
	gettimeofday(&finish,NULL);
  close(dev_fd);
	fps=(double)(fcount)/((finish.tv_sec-start.tv_sec)+(finish.tv_usec-start.tv_usec)/1e6);
	printf("\n%f fps, Saving collectected frames...\n",fps);
	
	for(i=0;i<fcount;i++)
	{
    FILE *img=NULL;
    char tmp[1024];
    
    sprintf(tmp,"%s_%03d_Y.pgm",output_base,i);
    
    if((img=fopen(tmp,"wb"))==NULL)
    {
      fprintf(stderr,"Can't open file %s for writing\n",tmp);
      break;
    } 
    
    fprintf(img,"P5\n%d %d\n255\n",fmt.fmt.pix.width,fmt.fmt.pix.height);
    if(fwrite(buffers[i],1,Ysize,img)<Ysize)
    {
      fprintf(stderr,"Can't write to file %s\n",tmp);
      fclose(img);
      break;
    }
    fclose(img);
    
    sprintf(tmp,"%s_%03d_CbCr.ppm",output_base,i);
    
    if((img=fopen(tmp,"wb"))==NULL)
    {
      fprintf(stderr,"Can't open file %s for writing\n",tmp);
      break;
    } 
    
    fprintf(img,"P5\n%d %d\n255\n",fmt.fmt.pix.width/2,fmt.fmt.pix.height*2);
    
    if(fwrite(buffers[i]+Ysize,1,CbCrsize*2,img)<CbCrsize*2)
    {
      fprintf(stderr,"Can't write to file %s\n",tmp);
      fclose(img);
      break;
    }
    fclose(img);
    
    printf("%d\t",i);
    fflush(stdout);
		free(buffers[i]);
  }
	
  printf("\n");
  free(buffers);
}
