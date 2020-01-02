#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void new_word(char* word){

char* temp;
char* remainder_word;
char* final_word;
int len = strlen(word);

int i,j;

if(word[0] == 'a' || word[0] == 'e' || word[0] == 'i' || word[0] == 'o' || word[0] == 'u' || word[0] == 'A' || word[0] == 'E' || word[0] == 'I' || word[0] == 'O' || word[0] == 'U'){
temp = malloc((len+2)*sizeof(char));

for(i=0;i<len;i++){
temp[i] = word[i];
 }

temp[i] = 'y';
temp[i+1] = 'a';
temp[i+2] = 'y';

printf("%s ", temp);
return;
}

else{

int word_count = 0;

for(i=0;i<len;i++){

 if(word[i] != 'a' && word[i] != 'e' && word[i] != 'i' && word[i] != 'o' && word[i] != 'u' && word[i] != 'A' && word[i] != 'A' && word[i] != 'I' && word[i] != 'O' && word[i] != 'U'){
  
  word_count++;
 // printf("%c\n",word[i]);
  }
 
 else{
  break;
 }
 
}

if(word_count == len){

printf("%s ", word);
return;
}

 temp = malloc((word_count)*sizeof(char));
 int c = 0;
 for(i=0;i<word_count;i++){
 temp[i]=word[i];
 }
 
 //printf("%s\n",temp);
 
 
 int len_1 = ((len-word_count));
 
 remainder_word = malloc(len_1*sizeof(char));
 
 for(i=word_count;i<len;i++){
 
   remainder_word[c]= word[i];
  
   c++;
   
  }
  
  // printf("%s\n", remainder_word);
 
 
 
 
  final_word = malloc((len+1)*sizeof(char));
  
  for(i=0;i<len_1;i++){
  
  final_word[i] = remainder_word[i];
  
   }
   
   j=0;
  for(i=len_1;i<len;i++){
   
    final_word[i] = temp[j];
    j++;
  
   }
   
   final_word[i] = 'a';
   final_word[i+1] = 'y';
  
  printf("%s ", final_word);
 
 }

}

int main(int argc, char** argv){

char* str;

int i,j;
for(i=1;i<argc;i++){

if(argv[1] == NULL){
exit(0);
}
new_word(argv[i]);


 }

return 0;
}
