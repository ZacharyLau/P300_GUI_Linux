
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../List.c" 
#define ltbrownColor 0xc0c0c0
#define labelWidth  640
#define labelHeight 622
#define plotWidth  615
#define plotHeight 600

#define plotWidthII 960
#define labelWidthII  1000
typedef struct color{
  int r; 
  int g;
  int b;
  }color;

typedef struct TwoDArray{

  double* array;
  int column;
  int row;
  int time;

  }TwoDArray;

void labeling_index(int max, int min, Display *display, Window win, int orientation);
void drawing_devision(Display *d, Window w);
//void flash_symbol_vertical_label(int max, Display *display, Window win, int isLabel);
void plotting(TwoDArray* lst, double max, double min, Display *display, Window win);
void r2plot(TwoDArray *lst);
void sample_index(double max, double min, Display *display, Window win);
void plot_devision(TwoDArray* lst  , Display *display, Window win);

void sampling(double max, double min, Display *display, Window win);
unsigned long int colorCode(double level);
unsigned char colormap(double level,char color);


int main(void) {
   TwoDArray *lst = (TwoDArray *)malloc(sizeof(TwoDArray));
   double temp1[205 * 8];
   lst -> array = temp1;
   int i;
   for(i=0;i<205*8;i++){
      temp1[i] = i%256;

   }
   lst -> column = 205;
   lst -> row = 8;
   lst -> time = 800;
   r2plot(lst);



   return 0;
}



void r2plot(TwoDArray *lst) {
   Display *d;
   Window w;
   Window plotLabel;
   Window sampleLabel;
   Window ptPlot;
   Window smPlot;

   int channelNum, time;
   time = lst -> time;
   channelNum = lst -> row; 

  

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

/*parent window */
   w = XCreateSimpleWindow(d, RootWindow(d, s), 100, 100, 900, 800, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSetNormalHints(d, w, &my_hints);  /* Where new_window is the new window */
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);

/*plot Label window */
   plotLabel = XCreateSimpleWindow(d, w, 60, 130, labelWidth+2, labelHeight , 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, plotLabel, ExposureMask | KeyPressMask);
   XMapWindow(d, plotLabel);


   ptPlot = XCreateSimpleWindow(d, plotLabel, 20, 0, plotWidth, plotHeight, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, ptPlot, ExposureMask | KeyPressMask);
   XMapWindow(d, ptPlot);



/* sample label window  */
   sampleLabel = XCreateSimpleWindow(d, w, 20 + labelWidth + 50, 130, 160, labelHeight, 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, sampleLabel, ExposureMask | KeyPressMask);
   XMapWindow(d, sampleLabel);

   smPlot = XCreateSimpleWindow(d, sampleLabel, 0, 0, 70, plotHeight, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, smPlot, ExposureMask | KeyPressMask);
   XMapWindow(d, smPlot);
                     
  
 // ************************* get the maximum and minimum *****************************
   int i;
   double max, min;
   max = lst -> array[0];
   min = lst -> array[0];
  
   int length;
   length = lst->column * lst->row;
  
   for(i=0;i<length;i++){
      if(max<lst->array[i]){
	 max = lst -> array[i];
      }
      if(min>lst->array[i]){
	 min = lst -> array[i];
      }
   }

   char tempstr[1];
   // ************************* get the maximum and minimum *****************************
   while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
	 sampling(max, min, d, smPlot);
	 plotting(lst, max, min, d, ptPlot);
         drawing_devision(d, smPlot);
         sample_index(max, min, d, sampleLabel);
         
         
	 labeling_index(channelNum, 1, d, plotLabel, 1);
	 plot_devision(lst , d, ptPlot);
  	 labeling_index(time, 0, d, plotLabel, 0);
 	 
	 sprintf(msg,"r2 Channels vs. Time");
         XDrawString(d, w, DefaultGC(d, s), 350,50, msg, strlen(msg));
        
         //sprintf(msg,"Left click to plot topography and responses");
         //XDrawString(d, w, DefaultGC(d, s), 280,70, msg, strlen(msg));

         sprintf(msg,"Press any key to end");
         XDrawString(d, w, DefaultGC(d, s), 350,90, msg, strlen(msg));

	 sprintf(msg,"TIME");
         XDrawString(d, w, DefaultGC(d, s), 350,140 + labelHeight, msg, strlen(msg));
	 
         sprintf(msg,"CHANNEL");
         for(i=0;i<7;i++){
	    sprintf(tempstr,"%c", (char)(msg[i]));
            XDrawString(d, w, DefaultGC(d, s), 50,140 + labelHeight/3 + i*12, tempstr, 1);
	 }
         
         
      }
      if (e.type == KeyPress)
         break;
   }
   XCloseDisplay(d);

}

void plot_devision( TwoDArray* lst , Display *display, Window win){

   int channel = lst -> row;
   int s = DefaultScreen(display);
   XSetForeground(display, DefaultGC(display, s), BlackPixel(display, s));
   int i;
   double diff = plotHeight / (double)(channel);
   for(i=1;i<channel;i++){ 
      XDrawLine(display, win, DefaultGC(display, s), 0,(diff * i),plotWidth,diff * i);
   }

   diff = plotWidth / (double)(lst -> column);
   for(i=1; i<lst -> time; i++){
      XDrawLine(display, win, DefaultGC(display, s), (diff * i),0,(diff * i),plotHeight);

   } 


}

void drawing_devision( Display *d, Window w){
   
   int s = DefaultScreen(d);
   XSetForeground(d, DefaultGC(d, s), BlackPixel(d, s));
   XSetLineAttributes(d, DefaultGC(d, s), 1, LineSolid, CapNotLast, JoinMiter);
   
   int i;

   int diff = plotHeight / 11;
   for(i=1;i<11;i++){
      XDrawLine(d, w, DefaultGC(d, s), 0,i*diff,5,i*diff);
      XDrawLine(d, w, DefaultGC(d, s), 65,i*diff,70,i*diff);

   }


}

void plotting(TwoDArray* lst, double max, double min, Display *display, Window win){
   int s = DefaultScreen(display);
   double  level;
   
   int i,c,r;
   double diff = (plotHeight)/ (double)(lst->row);
   XColor color; 
   
   for(i=0; i<(lst->column*lst->row);i++){
      r = i/lst->column;
      c = i%lst->column;
     
      level = lst->array[i]/(max - min);
      printf("\nlevel: %lf",level);
      XSetForeground(display, DefaultGC(display, s), colorCode( level));
      XFillRectangle(display, win, DefaultGC(display, s), c*3, (lst->row - r -1 )*diff, 3, diff);
   }


   

}

void sample_index(double max, double min, Display *display, Window win){

   char msg[100];
   int s = DefaultScreen(display);
   int i, diff;
   double div = (max - min) / 11;

   
   diff = plotHeight / 11 ;
   for(i=0; i<=11; i++){
      sprintf(msg,"%lf", (max - div*i));
      XDrawString(display, win, DefaultGC(display, s), 80,diff * i + 10, msg, strlen(msg));
   }
   


}
   
void labeling_index(int max, int min, Display *display, Window win, int orientation){

   char msg[100];
   int s = DefaultScreen(display);
   int i;
   double diff;
   //double div = (max - min) / 11;
//1 means vertical, 0 means horizonal

   if(orientation){//vertical
      diff = (plotHeight)/ (double)((max) * 2)  ;
      for(i=0; i<max; i++){
         sprintf(msg,"%d", (max - i));
         XDrawString(display, win, DefaultGC(display, s), 5,diff * i * 2 + diff, msg, strlen(msg));
	 
      }
   }else{
         diff = (plotWidth-(max/50))/(double)(max/100);
	 for(i=0; i<=(max/100); i++){
         sprintf(msg,"%d", (i*100));
         XDrawString(display, win, DefaultGC(display, s), i*diff + 20,plotHeight + 15, msg, strlen(msg));

      }
   }
//1 means vertical, 0 means horizonal

}



void sampling(double max, double min, Display *display, Window win){
   int s = DefaultScreen(display);
   double diff = (max - min)/(double)(plotHeight);
   int i;
   double level;
   for(i=plotHeight + 2; i>=0; i--){
      level = (i*diff+min)/(max - min);
      XSetForeground(display, DefaultGC(display, s), colorCode(level));
      XFillRectangle(display, win, DefaultGC(display, s), 0, plotHeight - i, 70, plotHeight -i - 3 );
   }

}


//unsigned char colormap(double level,char color)
unsigned char colormap(double level,char color){
  level = level * 63.0;
    level = round(level);
    level = level /63.0;
  int mult;
  switch(color)
  {
   case 'r':
   case 'R':
            level-=16.0/63.0;
           mult=31;
            break;
   case 'b':
   case 'B':
            level+=16.0/63.0;
            mult=31;
            break;
   default:
             mult=63;
  }

  level=31.0/63.0-level;
  if(level<0)
    level=-level;
  level=4.0*(24.0/63.0-level);
  if (level<0)
    level=0;
  if (level>1)
    level=1;
  return(round(level*mult));
}

unsigned long int colorCode(double level){
   return (colormap(level,'r')<<11|colormap(level,'g')<<5|colormap(level, 'b'));


}



