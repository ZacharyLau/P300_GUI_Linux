
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
#define labelWidth  600
#define labelHeight 420
#define plotWidth  580
#define plotHeight 400

void labeling_index(int max,  Display *display, Window win, int orientation);
void drawing_devision(int vDivision, int hDivision, Display *d, Window w);
void flash_symbol_vertical_label(int max, Display *display, Window win, int isLabel);
void plotting(list *lst, Display *display, Window win, int isPercentage);
void plot(list *lst, filename* name);


int main(void) {
   list *lst = (list *)malloc(sizeof(list));
   int temp1[] = {40, 60, 83, 83, 100, 100, 100, 90, 83, 60, 95};
   lst -> percentage = temp1;
   int temp2[] = {1, 3, 6, 8, 8, 8, 7, 8, 7, 6, 8};
   lst -> symbol = temp2;
   lst -> length = 11;
   lst -> capacity = 12;
   filename *name = (filename *)malloc(sizeof(filename));
   name -> name = "Dan's EEG S001";
   name -> length = strlen(name -> name);
   plot(lst, name);



   return 0;
}

void plot(list *lst, filename* name) {
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
                           BlackPixel(d, s), WhitePixel(d, s));
   XSetNormalHints(d, w, &my_hints);  /* Where new_window is the new window */
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);



/*percent correct window */
   percentCorrect = XCreateSimpleWindow(d, w, 20, 20, labelWidth+6, labelHeight, 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, percentCorrect, ExposureMask | KeyPressMask);
   XMapWindow(d, percentCorrect);
   
   pcPlot = XCreateSimpleWindow(d, percentCorrect, 0, 0, plotWidth, plotHeight, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, pcPlot, ExposureMask | KeyPressMask);
   XMapWindow(d, pcPlot);

/*symbol Minute window */
   symbolMinute = XCreateSimpleWindow(d, w, 20, labelHeight+40, labelWidth+6, labelHeight, 0,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, symbolMinute, ExposureMask | KeyPressMask);
   XMapWindow(d, symbolMinute);

   smPlot = XCreateSimpleWindow(d, symbolMinute, 0, 0, plotWidth, plotHeight, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, smPlot, ExposureMask | KeyPressMask);
   XMapWindow(d, smPlot);
   
   int numpnts=10;
   float v[10]={1,2,3,4,5,6,7,8,9,12};
   int pMax, sMax;
   int i;
   
   //testing list


   pMax = lst -> percentage[0];
   sMax = lst -> symbol[0];
 
   for(i=0;i<lst->length;i++){
      if(pMax<lst->percentage[i]){
	 pMax = lst -> percentage[i];
      }
      if(sMax<lst->symbol[i]){
	 sMax = lst -> symbol[i];
      }
   }
   
   lst->pMax = pMax;
   lst->sMax = sMax;
   // end of testing list
   while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
	 


         labeling_index(100, d, percentCorrect, 1);
         labeling_index(lst->length, d, percentCorrect, 0);
         labeling_index(sMax, d, symbolMinute, 1);
         labeling_index(lst->length, d, symbolMinute, 0);

         drawing_devision(100, lst->length, d, pcPlot);
         drawing_devision(sMax, lst->length, d, smPlot);

         plotting(lst, d, pcPlot, 1);
	 plotting(lst, d, smPlot, 0);
	 
	 XDrawString(d, w, DefaultGC(d, s), 680,50, "File Name: ", strlen("File Name: "));
         XDrawString(d, w, DefaultGC(d, s), 750,50, name -> name, name -> length);
	 char lbl[100];
         sprintf(lbl, "X: # Target Flashes");
	 XDrawString(d, w, DefaultGC(d, s), 680,390, lbl, strlen(lbl));
         sprintf(lbl, "Y: Percent Correct");
         XDrawString(d, w, DefaultGC(d, s), 680,420, lbl, strlen(lbl));

	 sprintf(lbl, "X: # Target Flashes");
	 XDrawString(d, w, DefaultGC(d, s), 680,830, lbl, strlen(lbl));
         sprintf(lbl, "Y: Symbol/Minute");
         XDrawString(d, w, DefaultGC(d, s), 680,860, lbl, strlen(lbl));

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

}

void drawing_devision(int vDivision, int hDivision, Display *d, Window w){
//draw board
   int s = DefaultScreen(d);
   XSetLineAttributes(d, DefaultGC(d, s), 1, LineSolid, CapNotLast, JoinMiter);
   //XDrawLine(d, w, DefaultGC(d, s), 0,0,0,plotHeight); 
   //XDrawLine(d, w, DefaultGC(d, s), 0,plotHeight-1,plotWidth,plotHeight-1);
   int i;
//draw vertical division
   if((int)(vDivision) == 100){
      int diff = plotHeight / 10;
      
      for(i=1;i<10;i++){
      
            XDrawLine(d, w, DefaultGC(d, s), 0,i*diff,9,i*diff);
	    XDrawLine(d, w, DefaultGC(d, s), plotWidth-9,i*diff,plotWidth,i*diff);
      }
   }else{
	    
	    flash_symbol_vertical_label((int)(vDivision),d, w, 0);	
   }
//draw horizontal division
   int diff = plotWidth / (hDivision - 1);
   for(i=1;i<hDivision - 1;i++){
      XDrawLine(d, w, DefaultGC(d, s), i*diff,0,i*diff,9);
      XDrawLine(d, w, DefaultGC(d, s), i*diff,plotHeight,i*diff,392);
      
      

   }


}

void plotting(list* lst, Display *display, Window win, int isPercentage){
   int s = DefaultScreen(display);
   double vUnit;
   int hUnit = plotWidth/(lst->length - 1);
   XSetLineAttributes(display, DefaultGC(display, s), 2, LineSolid, CapNotLast, JoinMiter);
   int i;
   if(isPercentage){
      vUnit = plotHeight/lst->pMax;
      for(i=0; i<lst->length - 1; i++){
         XDrawLine(display, win, DefaultGC(display, s), hUnit*i,plotHeight - lst->percentage[i]*vUnit,hUnit*(i+1),plotHeight - lst->percentage[i+1]*vUnit);

      }
   }else{
      vUnit = plotHeight/lst->sMax;
      for(i=0; i<lst->length-1; i++){
         XDrawLine(display, win, DefaultGC(display, s), hUnit*i,plotHeight - lst->symbol[i]*vUnit,hUnit*(i+1),plotHeight - lst->symbol[i+1]*vUnit);

      }
   }


}


   
void labeling_index(int max,  Display *display, Window win, int orientation){

   char msg[100];
   int s = DefaultScreen(display);
   int i, diff;
   

//1 means vertical, 0 means horizonal

   if(orientation){//vertical
      if((int)(max) == 100){
         diff = (int)((max)/10);
         for(i=0; i<=max; i++){
           
            sprintf(msg,"%d", ((int)(max) - diff*i));
            XDrawString(display, win, DefaultGC(display, s), plotWidth + 6,(plotHeight / 10 -1)*(i)+10, msg, strlen(msg));

         }
      }else{
	    flash_symbol_vertical_label((int)(max),display, win, 1);
      }
   }else{//horizontal
      int intMax = (int)(max);
      for(i=0;i<intMax;i++){
            int unit = (int)(plotWidth/(intMax-1) - 1) ;
	    //printf("unit: %d\n",unit);
            sprintf(msg,"%d",(int)((i+1)));
            XDrawString(display, win, DefaultGC(display, s), unit*(i)+2, labelHeight-4, msg, strlen(msg));
            }

   }

}


void flash_symbol_vertical_label(int max, Display *display, Window win, int isLabel){
   int s = DefaultScreen(display);
   char msg[100];
   int i;

   //calculate the distance for each division

      double unit = max / 400.0; //get the value for each pixel
  
      double div = max / 4.0;
      double temp1 = round(div);

      if((int)(temp1) == (int)(div)){
         temp1 += 1.0;
      }
      int temp = (int)(temp1);

      int division = (int)(round(temp/unit));


   if(isLabel){
   //write the top value
      sprintf(msg,"%d",max);
      XDrawString(display, win, DefaultGC(display, s), plotWidth + 6 , 10, msg, strlen(msg));     
      
      for(i = 0; i < 4; i++){
	 if(temp * i != max){
            sprintf(msg,"%d",temp * i);
 	    XDrawString(display, win, DefaultGC(display, s), plotWidth + 6, (labelHeight - 20 -(division * i)), msg, strlen(msg));
	 } 
      }

   }else{
//draw the first line
      //XDrawLine(display, win, DefaultGC(display, s), 0,0,9,0);

//draw the rest
      for(i = 0; i < 4; i++){
         if(temp * i != max){
            XDrawLine(display, win, DefaultGC(display, s), 0,(labelHeight - 20 -(division * i)),9,(labelHeight - 20 -(division * i)));
	    XDrawLine(display, win, DefaultGC(display, s), plotWidth - 9,(labelHeight - 20 -(division * i)),plotWidth ,(labelHeight - 20 -(division * i)));
         }
      }
   }



}


