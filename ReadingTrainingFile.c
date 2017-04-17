#include <stdio.h>
#include <string.h>
//#include "AbstractParameter.c"
#include "ReadingBufferMethods.c"
#include "Parameter.h"

typedef struct typelist{
  char *type;
}typelist;



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

//skip the title  
  get_crlf_line();

//set parameters
  //printf("\n%s\n",get_crlf_line());
//testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  
  int typeo = 0;
  typelist* type = malloc(1000);
  for(int i=0;i<(headerLen-stateVectorLen-1);i++){
    char* temp = get_parameter_line(get_crlf_line());
    int fg = 0;
    for(int j=0; j<typeo;j++){
      if(match(temp, typeo[j])){
        break;
        fg = 1;
      }else{
        continue;
      }
    }

    if(fg){
      type[typeo] = temp;
      typeo ++;
    } 
   
  }
   
  for(int i=0; i<=typeo; i++){
    printf("\ntype: %s \n", type[typeo]);
  }
  //get_parameter_line(get_crlf_line());

  fclose(fpGetLength); 
  fclose(fpRead);
  
} 

int match(char* str1, char* str2){



}

//testing!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int get_parameter_line(char* str){

  globalStr = str;

  trim_parameter(0);

  return trim_parameter(0);
  //printf("\ntype: %s\n", trim_parameter(0));

  //printf("\nname: %s\n", trim_parameter(1));

  //printf("\nvalue: %s\n", trim_parameter(0));

}

void get_headerLen_sourceCh_stateVectorLen(char* str){
//init globalStr
  globalStr = str;
//trimming process
  trim_parameter(1);
  headerLen = atoi(trim_parameter(0));
  printf("\n header length: %d \n",headerLen);
  
  trim_parameter(1);
  sourceCh = atoi(trim_parameter(0));
  printf("\n source channel: %d \n",sourceCh);
  
  trim_parameter(1);
  stateVectorLen = atoi(trim_parameter(0));
  printf("\n state vecotor Length: %d \n",stateVectorLen);
  
}

int trim_parameter(int isParameterName){
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
  if(isParameterName){ 
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
