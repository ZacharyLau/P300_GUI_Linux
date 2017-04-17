//LIBS = 'pkg-config --libs gtk+-3.0';
//CFLAGS = 'pkg-config --cflags gtk+-3.0';  
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define MAX_X 10.0
#define MAX_Y 10.0

float call_function(float x){
  return x*x;
}

int draw_graph(Display *display, Window win){
  Window root_return;
  int x_return, y_return;
  unsigned int width_return, height_return;
  unsigned int border_width_return, depth_return;
  
  GC gc;
  XGCValues gcv;
  
  int blackPixel = BlackPixel(display, DefaultScreen(display));
  int whitePixel = WhitePixel(display, DefaultScreen(display));

  int x,y;

  float x1, y1;
  float x2, y2;
  
  int w1, h1;
  int w2, h2;

  int i;

  gcv.background = whitePixel;
  gcv.foreground = blackPixel;

  gc = XCreateGC(display, DefaultRootWindow(display), GCForeground | GCBackground, &gcv);

  XGetGeometry(display, win, &root_return, &x_return, &y_return, &width_return, &height_return, &border_width_return, &depth_return);

  XDrawLine(display, win, gc, 0, height_return/2, width_return, height_return/2);
  XDrawLine(display, win, gc, width_return/2, 0, width_return/2, height_return);

  //draw the function

  for(w1=0;w1<width_return;w1++){
    
    x1 = (w1*2.0/width_return -1.0)*MAX_X;
    y1 = call_function(x1);
    h1 = (1.0-(y1/MAX_Y))*height_return/2.0;

    w2 = w1 + 1;
    x2 = (w2*2.0/width_return -1.0)*MAX_X;
    y2 = call_function(x2);
    h2 = (1.0-(y2/MAX_Y))*height_return/2.0;

    XDrawLine(display, win, gc, w1, h1, w2, h2);
    }

  

  for(x=-MAX_X; x<=MAX_X; x++){
    w1 = (1.0 + (x/MAX_X)) * width_return/2.0;
    XDrawLine(display, win, gc, w1, height_return/2+5, w1, height_return/2-5);   
    
  }


  for(y=-MAX_Y; y<=MAX_Y; y++){
    h1 = (1.0 - (y/MAX_Y)) * height_return/2.0;
    XDrawLine(display, win, gc, width_return/2-5, h1, width_return/2+5, h1);

  }


}

// emacs ftw!!!
int main(int argc, char *argv[]){
  Display *dpy;
  int screen;
  Window win, root_win;
  XEvent event;

  unsigned int depth;
  XSetWindowAttributes attrs;

  dpy = XOpenDisplay(NULL);
  
  if(dpy == NULL){
    fprintf(stderr, "Cannot open display \n");
    exit(1);
  }

  screen = DefaultScreen(dpy);
  depth = DefaultDepth(dpy, screen);
  root_win = RootWindow(dpy, screen);
  
  attrs.border_pixel = BlackPixel(dpy, screen);
  attrs.background_pixel = WhitePixel(dpy, screen);
  attrs.override_redirect = True;
  attrs.colormap = CopyFromParent;
  attrs.event_mask = ExposureMask | KeyPressMask;
  
  win = XCreateWindow(dpy, root_win, 700, 700, 500, 300, 0, depth, InputOutput, CopyFromParent, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &attrs);

  XMapWindow(dpy, win);

  while(1){
    XNextEvent(dpy, &event);
    if(event.type == Expose){
      draw_graph(dpy, win);
    }


    if(event.type == KeyPress){
      XDestroyWindow(dpy, win);
      XCloseDisplay(dpy);
      break;
    }

  }
}





