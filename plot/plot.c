
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
#define ltbrownColor 0xc0c0c0
#define labelWidth  600
#define labelHeight 420
#define plotWidth  580
#define plotHeight 400

void labeling_index(float max,  Display *display, Window win, int orientation);
void drawing_devision(float vDivision, int hDivision, Display *d, Window w);
void flash_symbol_vertical_label(int max, Display *display, Window win, int isLabel);

int main(void) {
   Display *d;
   Window w;
   Window percentCorrect;
   Window symbolMinute;
   Window pcPlot;
   Window smPlot;
   
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
   w = XCreateSimpleWindow(d, RootWindow(d, s), 100, 100, 1200, 900, 1,
                           ltbrownColor, ltbrownColor);
   XSetNormalHints(d, w, &my_hints);  /* Where new_window is the new window */
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);



/*percent correct window */
   percentCorrect = XCreateSimpleWindow(d, w, 20, 20, labelWidth+4, labelHeight, 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, percentCorrect, ExposureMask | KeyPressMask);
   XMapWindow(d, percentCorrect);
   
   pcPlot = XCreateSimpleWindow(d, percentCorrect, 20, 0, plotWidth+4, plotHeight, 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, pcPlot, ExposureMask | KeyPressMask);
   XMapWindow(d, pcPlot);

/*symbol Minute window */
   symbolMinute = XCreateSimpleWindow(d, w, 20, labelHeight+40, labelWidth+4, labelHeight, 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, symbolMinute, ExposureMask | KeyPressMask);
   XMapWindow(d, symbolMinute);

   smPlot = XCreateSimpleWindow(d, symbolMinute, 20, 0, plotWidth+4, plotHeight, 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, smPlot, ExposureMask | KeyPressMask);
   XMapWindow(d, smPlot);
   
   int numpnts=10;
   float v[10]={1,2,3,4,5,6,7,8,9,12};
   float max;
   int i;
   max=v[0];
   for(int i=0;i<10;i++){
      if(v[i]>max)
         max=v[i];
      
      }
   
  
  

   while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
	 int div = 13;
         labeling_index(100, d, percentCorrect, 1);
         labeling_index(max, d, percentCorrect, 0);
         labeling_index(div, d, symbolMinute, 1);
         labeling_index(max, d, symbolMinute, 0);

         drawing_devision(100, (int)(max), d, pcPlot);
         drawing_devision(div, (int)(max), d, smPlot);
       /*  XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
         for(i=1;i<=numpnts;i++){
            sprintf(msg,"%d",i);
            XDrawString(d, w, DefaultGC(d, s), 50*(i-1)+15, 490, msg, strlen(msg));
            }
         for(i=0;i<=numpnts;i++){
            sprintf(msg,"%d",(10-i)*10);
            XDrawString(d, w, DefaultGC(d, s), 0,40*(i-1)+85, msg, strlen(msg));
            }
         XDrawLine(d, w, DefaultGC(d, s), 20,20,10,10); */
      }
      if (e.type == KeyPress)
         break;
   }
   XCloseDisplay(d);
   return 0;
}

void drawing_devision(float vDivision, int hDivision, Display *d, Window w){
//draw board
   int s = DefaultScreen(d);
   XDrawLine(d, w, DefaultGC(d, s), 0,0,0,plotHeight); 
   XDrawLine(d, w, DefaultGC(d, s), 0,plotHeight-1,plotWidth,plotHeight-1);
//draw vertical division
   if((int)(vDivision) == 100){
      int diff = plotHeight / 10;
      for(int i=0;i<10;i++){
      
            XDrawLine(d, w, DefaultGC(d, s), 0,i*diff,9,i*diff);
      }
   }else{

	    
	    flash_symbol_vertical_label((int)(vDivision),d, w, 0);	
   }
//draw horizontal division
   int diff = plotWidth / (hDivision - 1);
   for(int i=0;i<hDivision;i++){
      
      XDrawLine(d, w, DefaultGC(d, s), i*diff,plotHeight,i*diff,392);
      

   }


}




   
void labeling_index(float max,  Display *display, Window win, int orientation){

   char msg[100];
   int s = DefaultScreen(display);
   int i, diff;
   

//1 means vertical, 0 means horizonal

   if(orientation){//vertical
      if((int)(max) == 100){
         diff = (int)((max)/10);
         for(i=0; i<=max; i++){
           
            sprintf(msg,"%d", ((int)(max) - diff*i));
            XDrawString(display, win, DefaultGC(display, s), 2,39*(i)+10, msg, strlen(msg));

         }
      }else{
	    flash_symbol_vertical_label((int)(max),display, win, 1);
	    
	

      }
   }else{//horizontal
      int intMax = (int)(max);
      for(i=0;i<intMax;i++){
            int unit = (int)(plotWidth/(intMax-1)) ;
	    //printf("unit: %d\n",unit);
            sprintf(msg,"%d",(int)((i+1)));
            XDrawString(display, win, DefaultGC(display, s), unit*(i)+17, labelHeight-4, msg, strlen(msg));
            }

   }

}


void flash_symbol_vertical_label(int max, Display *display, Window win, int isLabel){
   int s = DefaultScreen(display);
   char msg[100];

   //calculate the distance for each division

      double unit = max / 400.0; //get the value for each pixel
      //printf("unit: %lf \n",unit); 
      double div = max / 4.0;
      double temp1 = round(div);
printf("temp1: %lf \n", temp1);
      if((int)(temp1) == (int)(div)){
         temp1 += 1.0;
      }
      int temp = (int)(temp1);
printf("temp: %d \n", temp);
      int division = (int)(round(temp/unit));


   if(isLabel){
   //write the top value
      sprintf(msg,"%d",max);
      XDrawString(display, win, DefaultGC(display, s), 5, 10, msg, strlen(msg));     
      
      for(int i = 0; i < 4; i++){
	 if(temp * i != max){
            sprintf(msg,"%d",temp * i);
 	    XDrawString(display, win, DefaultGC(display, s), 5, (labelHeight - 20 -(division * i)), msg, strlen(msg));
	 } 
      }

   }else{
//draw the first line
      XDrawLine(display, win, DefaultGC(display, s), 0,0,9,0);

//draw the rest
      for(int i = 0; i < 4; i++){
         if(temp * i != max){
            XDrawLine(display, win, DefaultGC(display, s), 0,(labelHeight - 20 -(division * i)),9,(labelHeight - 20 -(division * i)));
         }
      }
   }



}


