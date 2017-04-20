//data[i][*] length: number of flashes
//data[0][*] : percentage of correct
//data[1][*] : symbol
typedef struct list{
  int length; 
  int capacity;
  int* symbol;
  int* percentage;
  int pMax;
  int sMax;
}list;

typedef struct filename{
  int length; 
  char* name;
  }filename;

void create_list(){
  list *lst = (list *)malloc(sizeof(list));
  lst -> capacity = 5;
  lst -> length = 0;
  
}


void list_insert(int value, int type){
  if(type == 0){


  }

}
