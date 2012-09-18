#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_ttf.h"
#include <math.h>

SDL_Surface *screen;

point p1 = {0,0};
point p2 = {0,0};
point p3 = {0,0};
point p4 = {0,0};
int midx = MX/2;
int midy = MY/2 - 50;

#define pi 3.141592653589
inline double d_rad(int a)
{
 return(a*pi)/180;
}

int rdof(double x)
{
  
 float k=x-int(x);
 if(k>.5)
  return int(x)+1;
 else
  return int(x);
}

void line(point p1, point p2)
{
     lineColor(screen, p1.x, p1.y, p2.x,p2.y, 0xFF00FF);
}

void line(point p1,int d1,point p2,int d2)
{
     lineColor(screen, p1.x, p1.y+d1, p2.x,p2.y+d2, 0xFF00FF);
}

void box(point p1, point p2, point p3, point p4)
{
     int r = 100;
     line(p1,p2);
     line(p2,p3);
     line(p3,p4);
     line(p4,p1);
     
     line(p1,0,p1,r);
     line(p2,0,p2,r);
     line(p3,0,p3,r);
     line(p4,0,p4,r);
     
     line(p1,r,p2,r);
     line(p2,r,p3,r);
     line(p3,r,p4,r);
     line(p4,r,p1,r);
     
}

void render()
{
  // Lock surface if needed
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;
      static int j = 0;
      float i, r1=100,r2=40;
      //LINE
      i = j*(3.14/180);
      cls(0);
      p1.x = rdof(midx+r1*cos(i));
      p1.y = rdof(midy+r2*sin(i)) ;
      p2.x = rdof(midx+r1*cos((3.14/2)+i));
      p2.y = rdof(midy+r2*sin((3.14/2)+i));
      p3.x = rdof(midx+r1*cos((3.14)+i));
      p3.y = rdof(midy+r2*sin((3.14)+i));
      p4.x = rdof(midx+r1*cos((3.14*1.5)+i));	
      p4.y = rdof(midy+r2*sin((3.14*1.5)+i));
      box(p1,p2,p3,p4);
      putpixel(p1,0xFF0000);
      putpixel(p2,0xFF0000);
      putpixel(p3,0xFF0000);
      putpixel(p4,0xFF0000);
	  //aalineColor(screen, 10, 10,20, 20, 0xFF00FF);
      j += 1;
      
      j = (j>360)?0:j;
      SDL_Delay(10);
      
      //sge_Line(,midy+r2*sin(i),,midx+r1*cos((3.14)+i),0xFF0000);
      
      /**for(float i=1;i<360;i+=1)
   	  {	     
         putpixel(midx+(offset-flag)*cos(d_rad(i)),midy+(offset-flag)*sin(d_rad(i)),0xFF0000);
         putpixel(midx+offset*cos(d_rad(i)),midy+offset*sin(d_rad(i)),0x00FF00);
       }  	
      if(offset>2*midx-250 || offset <0)
      	flag*=-1;
      offset+=flag;
      */
      /** //LINE(AA)
      sge_Line(screen, MX, 0, MX/2, MY/2, 0xFF0000);
      
      //LINE(MC)
      sge_mcLine(screen, 0, MY, MX/2, MY/2, 255,0,0,0,0,255);
      
      //REctangl border
      sge_Rect(screen, MX/2, MY/2, MX-2, MY-2, 0x00FF00);
      
      //FIlled Rectangle
      sge_FilledRect(screen, MX/2+20, MY/2+20, MX-20, MY-20, 0x7A150E);
      
      //Circle
      sge_Circle(screen, MX/2, MY/2, 250, 0x0000FF);
      
      //Filled circle
      sge_FilledCircle(screen, MX/2-200, MY/2-30, 50, 0xFFFFFF);
      
      //Ellipse
      sge_Ellipse(screen, MX/2, MY/2, 50,20, 0xF0FFFF);
      **/
      
  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);

  // Tell SDL to update the whole screen
  SDL_Flip(screen);
}


// Entry point
int main(int argc, char *argv[])
{
  init();
  // Main loop: loop forever.

  while (1)
  {
    // Do The display!
    render();
    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
          //dot.gKeyLeft = 1;
          p1 = update(p1,-1,0);
          break;
        case SDLK_RIGHT:
          //dot.gKeyRight = 1;
          p1 = update(p1,1,0);
          break;
        case SDLK_UP:
          //dot.gKeyUp = 1;
          p1 = update(p1,0,-1);
          break;
        case SDLK_DOWN:
          //dot.gKeyDown = 1;
          p1 = update(p1,0,1);
          break;
        }
        break;
        
      case SDL_QUIT:
        return(0);
      }
    }
  }
  return 0;

}

