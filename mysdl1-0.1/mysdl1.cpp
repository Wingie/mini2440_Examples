#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"
#include <math.h>
#include "SDL/SDL_gfxPrimitives.h"
SDL_Surface *screen;
bool draw = false;
int dx=0,dy=0;

void render()
{

  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;
      
    //if(draw)
		//putpixel(dx,dy,0xFF0000);
	circleColor(screen, MX/2, MY/2, 100, 0xFF00FF);
	aalineColor(screen, 0, 0,MX, MY, 0xFF00FF);

  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);
  // Tell SDL to update the whole screen
  SDL_Flip(screen);
}

int main(int argc, char *argv[])
{
  init();
  
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
