#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int checkPower(int n);
struct node** create_cache(int,int);
int get_index(unsigned long long int,int,int);
unsigned long long int get_tag(unsigned long long int,int,int);
struct node** search_cache(struct node**,int,unsigned long long int,char c,int);
void free_cache(struct node** arr, int A, int S);
struct node** prefetch_search_cache(struct node**,int,unsigned long long int, char, int,unsigned long long int,int,int,int,int,int);
int check_hit(struct node** arr, unsigned long long int add,int index,int block_offset,int index_bits,int S);
struct node** prefetch(struct node**,unsigned long long int address,int prefetch_size,int block_size,int block_offset, int S,int,int);

int cache_hits = 0;
int cache_misses = 0;
int reads = 0;
int writes = 0;


struct node{
unsigned long long int value;
struct node* next;
int valid;
int count;
};

struct node** create_cache(int A, int S){

struct node** arr = malloc(S * sizeof(struct node*));
int i, j;


for(i=0;i<S;i++){
j=0;
arr[i] = malloc(sizeof(struct node));

struct node* rear = NULL;
struct node* head = NULL;

 while(j < A){
 
 struct node* temp = malloc(sizeof(struct node));
 
 if(head == NULL && A != 1){
 struct node* temp1 = malloc(sizeof(struct node));
   temp->valid = 0;
   temp->next = NULL;
   head = temp;
   arr[i]->next = head;
   j++;
   
   temp1->valid = 0;
   temp->next = temp1;
   temp1->next = NULL;
   rear = temp1;
   j++;
   continue;
 }
 else if(head == NULL && A==1){
   temp->valid = 0;
   temp->next = NULL;
   head = temp;
   arr[i]->next = head;
   j++;
   break;
 }
 
 temp->valid = 0;
 rear->next = temp;
 temp->next = NULL;
 rear = temp;
 j++;
 }

}
return arr;
}

struct node** search_cache(struct node** arr,int index,unsigned long long int tag, char c,int A){

struct node* ptr;
struct node* rear;
struct node* head;
struct node* t;

if(A == 1){

head = arr[index]->next;
ptr = head;
if(ptr->value == tag && c=='R'){
cache_hits++;
return arr;
}
else if(ptr->value == tag && c=='W'){
cache_hits++;
writes++;
return arr;
}

if(c=='R'){//READ and MISS
cache_misses++;
reads++;
}
else if(c == 'W'){//WRITE and MISS
cache_misses++;
reads++;
writes++;
}

if(ptr->valid == 0){
ptr->value = tag;
ptr->valid = 1;
return arr;
}
ptr->value = tag;
return arr;
}

head = arr[index]->next;
ptr = head;
while(ptr!=NULL){
rear = ptr;
ptr = ptr->next;
}
ptr = head;
while(ptr!=NULL){
if(ptr->value == tag && c == 'R'){
cache_hits++;
return arr;
}
else if(ptr->value == tag && c == 'W'){
cache_hits++;
writes++;
return arr;
}
ptr=ptr->next;
}

if(c=='R'){//READ and MISS
cache_misses++;
reads++;
}
else if(c == 'W'){//WRITE and MISS
cache_misses++;
reads++;
writes++;
}

ptr = head;
while(ptr!=NULL){

if(ptr->valid == 0){
ptr->value = tag;
ptr->valid = 1;
return arr;
}
ptr=ptr->next;
}
ptr = head;
t = head;
head = ptr->next;
arr[index]->next = head;
t->next = NULL;
rear->next = t;
t->value = tag;
return arr;
}

struct node** prefetch_search_cache(struct node** arr,int index,unsigned long long int tag, char c, int prefetch_size, unsigned long long int address, int block_size, int block_offset,int index_bits,int S,int A){

struct node* ptr;
struct node* rear;
struct node* head;
struct node* t;

if(A == 1){

head = arr[index]->next;
ptr = head;

if(ptr->value == tag && c=='R'){
cache_hits++;
return arr;
}
else if(ptr->value == tag && c=='W'){
cache_hits++;
writes++;
return arr;
}

if(c=='R'){//READ and MISS
cache_misses++;
reads++;
}
else if(c == 'W'){//WRITE and MISS
cache_misses++;
reads++;
writes++;
}

if(ptr->valid == 0){
ptr->valid = 1;
}
ptr->value = tag;
arr = prefetch(arr,address,prefetch_size,block_size,block_offset,S,index_bits,A);
return arr;
}

head = arr[index]->next;
ptr = head;
while(ptr!=NULL){
rear = ptr;
ptr = ptr->next;
}

ptr = head;
while(ptr!=NULL){// Loop for searching the tag in the cache
if(ptr->value == tag && c == 'R'){//For a hit
cache_hits++;
return arr;
}
else if(ptr->value == tag && c == 'W'){
cache_hits++;
writes++;
return arr;
}
ptr=ptr->next;
}

if(c=='R'){//READ and MISS
cache_misses++;
reads++;
}
else if(c == 'W'){//WRITE and MISS
cache_misses++;
reads++;
writes++;
}

ptr = head;
while(ptr!=NULL){

if(ptr->valid == 0){
ptr->value = tag;
ptr->valid = 1;
arr = prefetch(arr,address,prefetch_size,block_size,block_offset,S,index_bits,A);
return arr;
}
ptr=ptr->next;
}
ptr = head;
t = head;
head = ptr->next;
arr[index]->next = head;
t->next = NULL;
rear->next = t;
t->value = tag;
arr = prefetch(arr,address,prefetch_size,block_size,block_offset,S,index_bits,A);
return arr;

}

struct node** prefetch(struct node** arr,unsigned long long int address,int prefetch_size,int block_size,int block_offset,int S,int index_bits,int A){

struct node* ptr;
struct node* rear;
struct node* head;
struct node* t;

int index;
unsigned long long int tag;
int i;
unsigned long long int prefetch_address;
prefetch_address = address;
int check = 0;

for(i=0;i<prefetch_size;i++){

 prefetch_address = prefetch_address + block_size;
 
 index = get_index(prefetch_address, block_offset,S);
 tag = get_tag(prefetch_address, block_offset, index_bits);

 check = check_hit(arr,tag,index,block_offset,index_bits,S);

 if(check == 0){//it's a MISS
 reads++;
 
 if(A==1){
 head = arr[index]->next;
 ptr = head;
 if(ptr->valid == 0){
ptr->valid = 1;
}
ptr->value = tag;
continue;
 
 }
 
 int a=0;
 
  head = arr[index]->next;
 ptr = head;
 
 while(ptr!=NULL){
rear = ptr;
ptr = ptr->next;
}
ptr = head;
 
while(ptr!=NULL){

if(ptr->valid == 0){
ptr->value = tag;
ptr->valid = 1;
a=1;
break;
}
ptr=ptr->next;
}
if(a==1){
continue;
}

ptr = head;
t = head;
head = ptr->next;
arr[index]->next = head;
t->next = NULL;
rear->next = t;
t->value = tag;
continue;

 }
 else if(check == 1){
  continue;
 }
 
}

return arr;
}

int check_hit(struct node** arr, unsigned long long int tag,int index,int block_offset,int index_bits,int S){
 
 struct node* ptr;
 struct node* head;
 
 head = arr[index]->next;
 ptr = head;
 
 while(ptr!=NULL){// Loop for searching the tag in the cache
if(ptr->value == tag){//For a hit
return 1;
}
ptr=ptr->next;
}
return 0;
}

void free_cache(struct node** arr, int A, int S){

int i;

 for(i=0;i<S;i++){
 struct node* temp = arr[i]->next;
 struct node* temp1;
 free(arr[i]);
 while(temp != NULL){
  temp1=temp->next;
  free(temp);
  temp = temp1;
 }
  
 }
 free(arr); 

}

int get_index(unsigned long long int add,int block_offset, int S){

int set_index = (add>>block_offset)%S;

return set_index;
}

unsigned long long int get_tag(unsigned long long int add, int block_offset, int index){

return add>>(block_offset+index);

}

int checkPower(int n){

while(n!=1){
 if(n%2 != 0){
 return 0;
 }
 n=n/2;
}
return 1;
}

int main(int argc, char** argv){

int A,S,prefetch_size,block_size;
char *cp;

int cache_size = atoi(argv[1]);
 block_size = atoi(argv[2]);

int ch = checkPower(cache_size);
int b = checkPower(block_size);

if(ch==0 || b==0){
printf("error\n");
exit(0);
}

if(argv[3][0] != 'f' && argv[3][0] != 'l'){
printf("error\n");
exit(0);
}

if(argv[4][0] == 'd'){
 A = 1;
 S = (cache_size/block_size);  
}
else if(argv[4][0] == 'a' && argv[4][5] == ':'){
int len,i,pow=0;
cp = argv[4];
len = strlen(cp);
char c;
for(i=0;i<len;i++){
c = cp[i];
if(isdigit(c)){
A = cp[i] - '0';
pow = checkPower(A);
if(pow == 0){
printf("error\n");
exit(0);
}
}

}

S = (cache_size/(block_size*A));

}
else if(argv[4][0] == 'a' && argv[4][5] == '\0'){
 S = 1; 
 A = (cache_size/block_size);
}
else{
printf("error\n");
exit(0);
}

prefetch_size = atoi(argv[5]);


int index_bits = log2(S);
int block_offset = log2(block_size);
struct node** arr = create_cache(A,S);

char c;
unsigned long long int add;
unsigned long long int tag;
int index;

FILE* fp = fopen(argv[6],"r");

if(fp == NULL){
printf("error\n");
exit(0);
}

if(fscanf(fp,"%c %llx\n",&c,&add) == EOF){
exit(0);
}

do{

if(c == '#'){
break;
}

index = get_index(add, block_offset,S);
tag = get_tag(add, block_offset, index_bits);

if(c == 'W'){
arr = search_cache(arr,index,tag,c,A);
}
else if(c == 'R'){
 arr = search_cache(arr,index,tag,c,A);
}


}while(fscanf(fp,"%c %llx\n", &c,&add)!=EOF);


printf("no-prefetch\n");
printf("Memory reads: %d\n", reads);
printf("Memory writes: %d\n", writes);
printf("Cache hits: %d\n", cache_hits);
printf("Cache misses: %d\n", cache_misses);

fclose(fp);

 cache_hits = 0;
 cache_misses = 0;
 reads = 0;
 writes = 0;

struct node** arr1 = create_cache(A,S);

fp = fopen(argv[6],"r");

while(fscanf(fp,"%c %llx\n", &c,&add)!=EOF){

if(c=='#'){
break;
}

index = get_index(add, block_offset,S);
tag = get_tag(add, block_offset, index_bits);

if(c == 'W'){
arr1 = prefetch_search_cache(arr1,index,tag,c,prefetch_size,add,block_size,block_offset,index_bits,S,A);
}
else if(c == 'R'){
 arr1 = prefetch_search_cache(arr1,index,tag,c,prefetch_size,add,block_size,block_offset,index_bits,S,A);
}


}

fclose(fp);

printf("with-prefetch\n");
printf("Memory reads: %d\n", reads);
printf("Memory writes: %d\n", writes);
printf("Cache hits: %d\n", cache_hits);
printf("Cache misses: %d\n", cache_misses);

free_cache(arr,A,S);
free_cache(arr1,A,S);

return 0; 
}
