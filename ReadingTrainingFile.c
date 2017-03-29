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
//skip around state vector 
  for(int i=0; i<stateVectorLen;i++){
    get_crlf_line();
  }
  
  get_crlf_line();
  printf("\n%s\n",get_crlf_line());
  
  fclose(fpGetLength); 
  fclose(fpRead);
  
}  

void get_headerLen_sourceCh_stateVectorLen(char* str){
//init globalStr
  globalStr = str;
//trimming process
  trim_parameter();
  headerLen = atoi(trim_parameter());
  printf("\n header length: %d \n",headerLen);
  
  trim_parameter();
  sourceCh = atoi(trim_parameter());
  printf("\n source channel: %d \n",sourceCh);
  
  trim_parameter();
  stateVectorLen = atoi(trim_parameter());
  printf("\n state vecotor Length: %d \n",stateVectorLen);
  
}

int trim_parameter(){
  int i;
  for(i=0; i<strlen(globalStr); i++){
    //printf("current char: %c\n",globalStr[i]);
    if(globalStr[i] != ' '){
      continue;
    }else{
      break;
    }
  }
  
  char* retstr = malloc(i);
  if(globalStr[0]<47  || globalStr[0]>59){ 
    memcpy(retstr, &globalStr[0], i-1);
  }else{
    memcpy(retstr, &globalStr[0], i);
  }

  globalStr = globalStr + i + 1;
  return retstr;
}


int main(int agrc, char** agrv){

  read_training_file("/home/zach/GUI_Project/data/jess.dat");
  

}
