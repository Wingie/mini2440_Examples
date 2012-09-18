#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"
#include <math.h>
#include "SDL/SDL_gfxPrimitives.h"
SDL_Surface *screen;
bool draw = false;
int dx=0,dy=0;

#define PITCH (screen->pitch / 4)

void initbg()
{
	int x1 = MX/2, y1 = MY/2-50;
	Sint16 xarr1[] = {x1,x1-20,x1+20};
	Sint16 yarr1[] = {y1,y1+40,y1+40};
  filledPolygonColor(screen, xarr1,yarr1, 3, 0xFF07FF);
  
	Sint16 xarr2[] = {x1+7,x1-7,x1-40,x1+40};
	Sint16 yarr2[] = {y1+40,y1+40,y1+80,y1+80};
  filledPolygonColor(screen, xarr2,yarr2, 4, 0xFF07FF);
  
  Sint16 xarr3[] = {x1+25,x1-25,x1-60,x1+60};
	Sint16 yarr3[] = {y1+80,y1+80,y1+120,y1+120};
  filledPolygonColor(screen, xarr3,yarr3, 4, 0xFF07FF);
  boxColor(screen,x1-7,y1+120,x1+7,MY,0xFF07FF);
  /*boxColor(screen,50,50,90,90,0xFF07FF);
  boxColor(screen,130,130,180,200,0xFF07FF);
  boxColor(screen,200,40,220,50,0xFF07FF);
  boxColor(screen,120,40,150,80,0xFF07FF);
  boxColor(screen,90,200,120,250,0xFF07FF);
  boxColor(screen,95,95,110,125,0xFF07FF);
  boxColor(screen,285,195,300,220,0xFF07FF);*/
}

void newsnow()
{
  int i;
  for (i = 0; i < 8; i++)
    ((unsigned int*)screen->pixels)[rand() % MX + 1] = 0xffffff;
}

void snowfall()
{
  int i, j;
  unsigned int *fb = (unsigned int*)screen->pixels;
  for (j = MY-2; j >= 0; j--)
  {
    int ypos = j * PITCH;
    for (i = 1; i < MX-2; i++)
    {
      if (fb[ypos + i] == 0xffffff)
      {
        if (fb[ypos + i + PITCH] == 0)
        {
          fb[ypos + i + PITCH] = 0xffffff;
          fb[ypos + i] = 0;
        }
        else
        if (fb[ypos + i + PITCH - 1] == 0)
        {
          fb[ypos + i + PITCH - 1] = 0xffffff;
          fb[ypos + i] = 0;
        }
        else
        if (fb[ypos + i + PITCH + 1] == 0)
        {
          fb[ypos + i + PITCH + 1] = 0xffffff;
          fb[ypos + i] = 0;
        }
      }
    }
  }
}

void render()
{   
  // Lock surface if needed
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0) 
      return;

  // Ask SDL for the time in milliseconds
  int tick = SDL_GetTicks();
	
  initbg();
  newsnow();
  snowfall();

  // Unlock if needed
  if (SDL_MUSTLOCK(screen)) 
    SDL_UnlockSurface(screen);

  // Tell SDL to update the whole screen
  SDL_UpdateRect(screen, 0, 0, MX, MY);    
}

int main(int argc, char *argv[])
{
  init();
  //initsnow();
  while (1)
  {
    render();
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

      switch (event.type) {
            case SDL_MOUSEMOTION:
                printf("###Mouse moved by %d,%d to (%d,%d)\n", 
                       event.motion.xrel, event.motion.yrel,
                       event.motion.x, event.motion.y);
                dx = event.motion.x;
                dy = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("***Mouse button %d pressed at (%d,%d)\n",
                       event.button.button, event.button.x, event.button.y);
                dx = event.button.x;
                dy = event.button.y;
                draw = true;
                break;
            case SDL_MOUSEBUTTONUP:
				draw = false;
				break;
            case SDL_QUIT:
                exit(0);
        }
    }
  }
  return 0;
}
