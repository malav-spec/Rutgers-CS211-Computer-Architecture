#include <stdio.h>
#include <stdlib.h>

struct node{

int data;
struct node* right;
struct node* left;
};


void display_tree(struct node* root);
void insert_value(int);
void search_value(int);




struct node* root = NULL;

void display_tree(struct node* root){
  if(root == NULL){
  return;
  }
 
  display_tree(root->left);
  printf("%d\t " ,root->data);
  display_tree(root->right);
} 

void search_value(int value){

int height = 1;

struct node* prev = NULL;
struct node* ptr = root;

while(ptr != NULL){

  if(ptr->data == value){
   printf("present %d\n" , height);
   return;
   }
  
  else if(value < ptr->data){
  prev = ptr;
  ptr = ptr->left;
  height++;
  }
  
 else{
  prev = ptr;
  ptr = ptr->right;
  height++;
  }
  
 }

 printf("absent\n");
 return;
}

void insert_value(int value){

struct node* temp = malloc(sizeof(struct node));
int height = 1;
if(root == NULL){

temp->data = value;
root = temp;
printf("inserted %d\n" , height);
return;
 }
 
 struct node* prev = NULL;
 struct node* ptr = root;
 
 temp->data = value;
 
 while(ptr != NULL){
 
 if(temp->data == ptr->data){
 printf("duplicate\n");
 return;
 }
 
 else if(temp->data < ptr->data){
  prev = ptr;
  ptr = ptr->left;
  height++;
  }
 else{
  prev = ptr;
  ptr = ptr->right;
  height++;
  }
  
 }// end while
 
 
 if(temp->data < prev->data){
 
 
 
 prev->left = temp;
 
 printf("inserted %d\n" , height); 
 }
 else{
 
 prev->right = temp;
 printf("inserted %d\n" , height); 
 
  }
  
}

int main(int argc, char** argv){

int num = 0;
char chr = ' ';

FILE* fp = fopen(argv[1],"r");

if(fp == NULL){
printf("error\n");
exit(0);
}

if(fscanf(fp,"%c\t %d",&chr,&num)==EOF){
exit(0);
}


do{

if(chr == 'i'){

  insert_value(num);
  }
else if(chr == 's'){

  search_value(num);

  }
  
}while(fscanf(fp, "%c\t %d \n", &chr, &num)!=EOF);

fclose(fp);

return 0;
}
