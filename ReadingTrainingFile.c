#include <stdio.h>
#include <string.h>
//#include "AbstractParameter.c"
#include "ReadingBufferMethods.c"
FILE *fpGetLength;
FILE *fpRead;
int headerLen;
int sourceCh;
int stateVectorLen;
int trim_parameter_name();
char* globalStr;

void read_training_file(char* address){
  fpGetLength = fopen(address, "r");
  fpRead = fopen(address, "r");

  init_reading(fpGetLength, fpRead);
  get_headerLen_sourceCh_stateVectorLen(get_crlf_line());


  fclose(fpGetLength); 
  fclose(fpRead);
  
}  

void get_headerLen_sourceCh_stateVectorLen(char* str){
//init globalStr
  globalStr = str;
//trimming process
  trim_parameter_name();
  
  
  

}

int trim_parameter_name(){
  int i;
  for(i=0; i<strlen(globalStr); i++){
    //printf("current char: %c\n",globalStr[i]);
    if(globalStr[i] < 48 || globalStr[i] > 57){
      continue;
    }else{
      break;
    }
  }
  
  char* retstr = malloc(i-1);
  memcpy(retstr, &globalStr[0], i-2);
  globalStr = globalStr + i;
  return retstr;
}


int main(int agrc, char** agrv){

  read_training_file("/home/zach/GUI_Project/data/jess.dat");
  

}
