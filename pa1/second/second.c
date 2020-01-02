#include <stdio.h>
#include <stdlib.h>


void insert(int data);
void print_list();
void free_list();
void delete();


struct node{

int data;
struct node* next;

};

struct node* head = NULL;

void insert(int data){

struct node* temp = malloc(sizeof(struct node));

if(head == NULL){
   temp->data = data;
   temp->next=NULL;
   head = temp;
   return;
   }


temp->data=data;



 if(temp->data < head->data){
 
 temp->next = head;
 head=temp;
 return;
 }
 
 struct node* prev = head;
struct node* ptr = head->next;

do{

 if(prev->data == temp->data){
      return;
       }

 else if(ptr == NULL && (prev->data < temp->data)){
 
 prev->next=temp;
 temp->next=NULL;
 break;
 }
 
 else if(ptr->next == NULL && (temp->data > ptr->data)){
 ptr->next=temp;
 temp->next=NULL;
 break;
 }
 
 else if(ptr->data > temp->data){
 
 prev->next=temp;
 temp->next=ptr;
 break;
 }
 
 prev=prev->next;
 
 ptr=ptr->next; 
 
}while(ptr != NULL);
  
 
}

void print_list(){

struct node* temp = head;
struct node* temp2 = head;

int c=0;
while(temp2 !=NULL){
c++;
temp2=temp2->next;
}

printf("%d\n", c);

while(temp != NULL){

if(temp->next == NULL){
printf("%d", temp->data);
break;
 }
  printf("%d\t", temp->data);
  temp=temp->next;
 
  }
  
}

void free_list(){

struct node* temp = head;

while(temp != NULL){
struct node* temp2 = temp;
temp=temp->next; 
free(temp2);

  } 

}

void delete(int data){

if(head == NULL){
return;
}

struct node* prev = head;
struct node* ptr = prev->next;

if(prev->data == data){
head = ptr;
return;
}

while(ptr !=NULL){

if(ptr->data == data && ptr->next!=NULL){    
 prev->next = ptr->next;
 break;
  }
  
if(ptr->next == NULL && ptr->data == data){
prev->next = NULL;
   break;
    }

prev=prev->next;
ptr=ptr->next;

} 

}

int main(int argc, char** argv){



int num=0;
char chr =' ';

FILE* fp = fopen(argv[1] , "r");

if(fp == NULL){
printf("error\n");
exit(0);
}

if(fscanf(fp,"%c\t %d",&chr,&num)==EOF){
printf("0\n");
exit(0);
}


do{

if(chr == 'i'){

  insert(num);
  }
else if(chr == 'd'){

  delete(num);

  }
}while(fscanf(fp, "%c\t %d \n", &chr, &num)!=EOF);

fclose(fp);

print_list();
free_list();

return 0;
}
