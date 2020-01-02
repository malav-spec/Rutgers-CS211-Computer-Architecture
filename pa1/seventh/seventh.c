#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_last_char(char*);

char get_last_char(char* str){

int len,i;
char chr;

len = strlen(str);

for(i=0;i<len;i++){

chr = str[i];
  }
return chr;
}

int main(int argc, char** argv){

int i,j=0;
char c;
char* s;

 s = malloc(argc*sizeof(char));
 
 for(i=1;i<argc;i++){
 
 c = get_last_char(argv[i]);
 
 if(j <= argc-1){
 
   s[j]=c;
   j++;
 
    }
  } 
  printf("%s\n",s);
  free(s);
  return 0;
}
