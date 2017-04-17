
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
int main(void) {
   Display *d;
   Window w;
   XEvent e;
   char msg[100];
   int s;
   XSizeHints    my_hints = {0};

   my_hints.flags  = PPosition | PSize;     /* I want to specify position and size */
 
   d = XOpenDisplay(NULL);
   if (d == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
   }
 
   s = DefaultScreen(d);


   w = XCreateSimpleWindow(d, RootWindow(d, s), 50, 50, 500, 500, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSetNormalHints(d, w, &my_hints);  /* Where new_window is the new window */
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);

   int i,numpnts=10;
   float v[10]={50,60,75,76,80,83.333,85,90,100},max,min;

   min=max=v[0];
   for(i=1;i<10;i++){
      if(v[i]>max)
         max=v[i];
      if(v[i]<min)
         max=v[i];
      }

   while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
         XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
         for(i=1;i<=numpnts;i++){
            sprintf(msg,"%d",i);
            XDrawString(d, w, DefaultGC(d, s), 50*(i-1)+15, 490, msg, strlen(msg));
            }
         for(i=0;i<=numpnts;i++){
            sprintf(msg,"%d",(10-i)*10);
            XDrawString(d, w, DefaultGC(d, s), 0,40*(i-1)+85, msg, strlen(msg));
            }
         XDrawLine(d, w, DefaultGC(d, s), 20,20,10,10);
      }
      if (e.type == KeyPress)
         break;
   }
   XCloseDisplay(d);
   return 0;
}

