#define COLOR 0xFF00FF
#define PITCH (screen->pitch / 4)
#define MX 320
#define MY 240
const SDL_Rect rect = {0,0,MX,MY};
#include <math.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_gfxPrimitives.h"

extern SDL_Surface *screen;

struct point
{
      int x;
      int y;   
};

point update(point p, int x = 0, int y = 0)
{
 p.x += x;
 p.y += y;
 if(p.x > MX)
        p.x = MX;
 if(p.y > MY)
        p.y = MY;
 return p;
}

void putpixel(point p, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = p.y * (screen->pitch / 4);
  ptr[lineoffset + p.x] = color;
}

void putpixel(int x,int y, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = y * (screen->pitch / 4);
  ptr[lineoffset + x] = color;
}

void shutdown()
{
    SDL_FreeSurface(screen);
    SDL_Quit();
}
int cls(int c = 0)
{
  int i, j;
  for (i = 0; i < MX; i++)
  {  
      for (j = 0; j < MY; j++)
        putpixel(i,j,c);
  }
  return c;
}



void init()
{
// Initialize SDL's subsystems - in this case, only video.

  if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register shutdown to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(shutdown);
  

  // Attempt to create a 640x480 window with 32bit pixels.
  screen = SDL_SetVideoMode(MX, MY, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    
  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }
  

  
 //Hide mouse cursor
  //SDL_ShowCursor(0);
  // Set the title of our window.
    SDL_WM_SetCaption("WWS", 0);
    SDL_SetClipRect(screen,&rect);
}

