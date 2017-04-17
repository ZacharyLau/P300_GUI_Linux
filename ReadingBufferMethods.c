#include <stdio.h>
#include <string.h>
#include <stdlib.h>


FILE *fpGetLength;
FILE *fpRead;
int character;
char* buffer;
int get_crlf_line();

void init_reading(FILE* fpgl, FILE* fpr){
  fpGetLength = fpgl;
  fpRead = fpr;
}



int get_crlf_line(){
  buffer = NULL;
  int length = 0;  
//get length  
  while((character = fgetc(fpGetLength)) != 13 ){  
    length++;    
  }

//put actual string into buffer
  buffer = malloc(length);
  fread(buffer, length+1, 1, fpRead);   
  fgetc(fpGetLength);
  fgetc(fpRead);
  return buffer;
}
