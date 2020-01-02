#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{

int data;
struct node* right;
struct node* left;
};

void display_tree(struct node* root);
void insert_value(int);
void search_value(int);
void delete_value(int);

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

void delete_value(int value){

struct node* temp = malloc(sizeof(struct node));


struct node* prev = NULL;
struct node* ptr = root;
 

/*if(check == true && root->left == NULL && root->right == NULL){
root = NULL;
}*/
while(ptr != NULL){

if(ptr->right == NULL && ptr->left == NULL && ptr->data != value){
printf("fail\n");
return;
}

if(ptr->data == value){
  break;
  }
 else if(ptr->data < value){
 prev= ptr;
 ptr = ptr->right;
 }
 else {
 prev = ptr;
 ptr = ptr->left;
 }
 
}//end while

if(prev == NULL){

if(ptr->right == NULL && ptr->left == NULL){
root = NULL;
printf("success\n");
return;
}

 else if(ptr->right != NULL && ptr->left != NULL){//2 child case
 
 struct node* count = ptr->right;
 struct node* prev_count = ptr;
 
 if(count->left == NULL && count->right == NULL){
  ptr->data = count->data;
  ptr->right = NULL;
  printf("success\n");
  return;
 }
 else if(count->left == NULL && count->right != NULL){
 
 ptr->data = count->data;
 ptr->right = count->right;
 printf("success\n"); 
 return;
 }
 else{
 
 while(count->left != NULL){
 prev_count = count;
 count = count->left;
  }
  
  ptr->data = count->data;
  
  if(count->right != NULL){
  prev_count->left = count->right;
  printf("success\n");
  return;
  }
  
  prev_count->left = NULL;
  printf("success\n");
  return;
  }
 }
 
 else if(ptr->right == NULL && ptr->left !=NULL){
 
 ptr->data = ptr->left->data;
 if(ptr->left->left != NULL){
 ptr->left = ptr->left->left;
 printf("success\n");
 return;
 }
 else{
 ptr->left = NULL;
 printf("success\n");
 return;
 }
 
 }
 
 else{
 
 ptr->data = ptr->right->data;
 
 if(ptr->right->right != NULL){
 ptr->right = ptr->right->right;
 printf("success\n");
 return;
 }
 else{
 ptr->right = NULL;
 printf("success\n");
 return;
 }
 
 }

}

 if(ptr->right == NULL && ptr->left == NULL){//leaf node case
  
  if(prev->right == NULL && prev->left != NULL){
  prev->left = NULL;
  printf("success\n");
  }
  else if(prev->right != NULL && prev->left == NULL){
  prev->right = NULL;
  printf("success\n");
  
  }
  
 }
 
 else if(ptr->right != NULL && ptr->left != NULL){//2 child case
 
 struct node* count = ptr->right;
 struct node* prev_count = ptr;
 
 if(count->left == NULL && count->right == NULL){
  ptr->data = count->data;
  ptr->right = NULL;
  printf("success\n");
 }
 else if(count->left == NULL && count->right != NULL){
 
 ptr->data = count->data;
 ptr->right = count->right;
 printf("success\n"); 
 }
 else{
 
 while(count->left != NULL){
 prev_count = count;
 count = count->left;
  }
  
  ptr->data = count->data;
  
  if(count->right != NULL){
  prev_count->left = count->right;
  printf("success\n");
  return;
  }
  
  prev_count->left = NULL;
  printf("success\n");
  
  }
 }
 
 else if(prev->left != NULL && ptr->right != NULL && ptr->left == NULL){
 prev->right = ptr->right;
 printf("success\n");
 }
 
 else if(prev->left != NULL && ptr->right == NULL && ptr->left != NULL){
 prev->right = ptr->left;
 printf("success\n");
 }
 
  
 else if(prev->right != NULL && ptr->right == NULL && ptr->left != NULL){
 
 prev->left = ptr->left;
 printf("success\n");
 }
 
 else if(prev->right != NULL && ptr->right != NULL && ptr->left == NULL){
 prev->right = ptr->right;
 printf("success\n");
 
 }
 
 else if(ptr->right == NULL && ptr->left != NULL){//1 child case
 prev->left = ptr->left;
 printf("success\n");
 }
 
 else if(ptr->right != NULL && ptr->left == NULL){
 prev->right = ptr->right;
 printf("success\n");
 }

}//end of function

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
 else if(chr == 'd'){
 
 delete_value(num);
 }
  
}while(fscanf(fp, "%c\t %d \n", &chr, &num)!=EOF);

fclose(fp);

/*display_tree(root);
printf("\n");
*/
return 0;
}
