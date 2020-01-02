#include <stdio.h>
#include <stdlib.h>


struct node* arr[1000];

int hash_function(int);
void insert_key(int);

void search(int);
void free_table();

int hash_function(int key){

return (key%1000);

}

struct node{

int value;
struct node* next;

};


void insert_key(int key){

if(key < 0){

int duplicate_key = key;
int dup_hash = key*(-1);

int hash = hash_function(dup_hash);

struct node* temp = malloc(sizeof(struct node));
temp->value = duplicate_key;

if(arr[hash] == NULL){

 arr[hash] = temp;
 temp->value = duplicate_key;
 temp->next = NULL;
 
 printf("%s\n", "inserted");
 return;
  }

else {

struct node* count = malloc(sizeof(struct node));
count  = arr[hash];
if(count->value == duplicate_key){

printf("duplicate\n");
return;
}

while(count->next != NULL){

if(count->value == duplicate_key){

printf("duplicate\n");
return;
}
count = count->next;

}

temp->value = duplicate_key;

count->next = temp;
temp->next = NULL;

printf("inserted\n");
return;
 }

}

int hash = hash_function(key);

struct node* temp = malloc(sizeof(struct node));
temp->value = key;

if(arr[hash] == NULL){

 arr[hash] = temp;
 temp->value = key;
 temp->next = NULL;
 
 printf("%s\n", "inserted");
 return;
  }

else {

struct node* count = malloc(sizeof(struct node));
count  = arr[hash];
if(count->value == key){

printf("duplicate\n");
return;
}

while(count->next != NULL){

if(count->value == key){

printf("duplicate\n");
return;
}
count = count->next;

}

temp->value = key;

count->next = temp;
temp->next = NULL;

printf("inserted\n");
 }

}


/*void print_index_list(int key){

struct node* count = malloc(sizeof(struct node));

int hash = hash_function(key);

count = arr[hash];

if(count == NULL){

printf("Empty index");
 }

while(count!= NULL){
 
 printf("%d\t", count->value);
 count = count->next;
 
  }

}*/

void search(int key){

if(key<0){

int duplicate_key = key;
int dup_hash = key*(-1);

struct node* count = malloc(sizeof(struct node));

int hash = hash_function(dup_hash);

count = arr[hash];

if(count == NULL){

printf("absent\n");
return;

 }

  else{

   while(count!= NULL){
    
      if(count->value == duplicate_key){
       printf("present\n");
       return;
        }  
      if(count->value != duplicate_key && count->next == NULL){
      
      printf("absent\n");
      return;
      }
      count = count->next;
     }
  } 

}

struct node* count = malloc(sizeof(struct node));

int hash = hash_function(key);

count = arr[hash];

if(count == NULL){

printf("absent\n");
return;

 }

  else{

   while(count!= NULL){
    
      if(count->value == key){
       printf("present\n");
       return;
        }  
      if(count->value != key && count->next == NULL){
      
      printf("absent\n");
      return;
      }
      count = count->next;
     }
  } 
}

void free_table(){

int i;

for(i=0;i<1000;i++){

if(arr[i] != NULL){

struct node* temp = malloc(sizeof(struct node));

temp = arr[i];

while(temp != NULL){

struct node* temp2 = malloc(sizeof(struct node));
temp2 = temp;
temp=temp->next;
free(temp2);

       }
    }
 }

}

int main(int argc, char** argv){

int num = 0;
char chr = ' ';

FILE* fp = fopen(argv[1],"r");

if(fp == NULL){
exit(0);
}

if(fscanf(fp,"%c\t %d", &chr,&num) == EOF){
exit(0);
  }

int copy_key=0;

do{

if(chr == 'i'){

insert_key(num);
 }
 
else if(chr == 's'){

search(num);

 }
 
}while(fscanf(fp,"%c\t %d", &chr,&num) != EOF);

fclose(fp);

free_table();

return 0;
}
