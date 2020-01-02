#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void traverse_hexadoku(char**,int,int);
void get_submatrix(char**,int,int);
void linear_search(char, int*);
void print_matrix(char**,int,int);
void check_matrix(char**,int,int);
void check_final_matrix(char**,char*,char*);
void free_matrix(char** matrix,int row);
void solver(char** matrix,int row_pos,int col_pos,char* row_arr,char* col_arr);
int size = 16;
char arr[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int check_arr[16]; 
int x;

void traverse_hexadoku(char** matrix, int row, int col){

int i,j;
char chr;
int count = 0;

/*for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 
 printf("%c\t" , matrix[i][j]);
 check_matrix(matrix, 16,16);
 }
printf("\n");
}*/
//printf("\n");
//printf("\n");

for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 
   if(matrix[i][j] == '-'){
   count++;
   get_submatrix(matrix, i ,j);
   }
   
  
 }
 
 }
 
 
 /*
 for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 
   if(matrix[i][j] == '?'){
   count++;
   get_submatrix(matrix, i ,j);
   }
 
 }
 
 }*/
 
//printf("%d\n\n", count);
//hex_solver(matrix, 5 ,3);
print_matrix(matrix, 16,16);
free_matrix(matrix,16);
//exit(0);
}

void get_submatrix(char** matrix, int row_pos, int col_pos){

char** sub_matrix;
char* row_arr;
char* col_arr;
int sub_row_start = 0;
int sub_col_start = 0;
int sub_row_end = 0;
int sub_col_end = 0;
int i ,j;
int row = 16;
int col = 16;
char* temp_arr;

//INITIALIZE THE CHECK ARRAY
for(i=0;i<16;i++){
check_arr[i] = 0;
}

row_arr = malloc(16*sizeof(char));
col_arr = malloc(16*sizeof(char));
temp_arr = malloc(16*sizeof(char));



sub_matrix = malloc(4*sizeof(char*));//allocating memory to sub matrix
for(i=0;i<4;i++){

sub_matrix[i] = malloc(4*sizeof(char));

}

//GET ROWS
 for(j=0;j<col;j++){
 row_arr[j] = matrix[row_pos][j];
 linear_search(row_arr[j], check_arr);
 //printf("%c\t", row_arr[j]);
 }
 
//printf("\n");


//GET COLUMNS
for(i=0;i<row;i++){
col_arr[i] = matrix[i][col_pos]; 
linear_search(col_arr[i], check_arr);
 //printf("%c\t", col_arr[i]);
 
 }
 //printf("\n");
 
//GET SUB MATRIX ROW RANGE
if(row_pos%4 == 0){//rp is the first number of submatrix
sub_row_start = row_pos;
sub_row_end = row_pos + 3;
} 
else if((row_pos+1)%4 == 0){//rp is the last number of submatrix
sub_row_start = row_pos - 3;
sub_row_end = row_pos;
}
else if((row_pos-1)%4 == 0){//rp is the second number of the submatrix
sub_row_start = row_pos - 1;
sub_row_end = sub_row_start + 3;
}
else if((row_pos-2)%4 == 0){
sub_row_start = row_pos - 2;
sub_row_end = sub_row_start +3;
}

//GET SUB MATRIX COLUMNS RANGE
if(col_pos%4 == 0){//cp is the first number of submatrix
sub_col_start = col_pos;
sub_col_end = col_pos + 3;
} 
else if((col_pos+1)%4 == 0){//cp is the last number of submatrix
sub_col_start = col_pos - 3;
sub_col_end = col_pos;
}
else if((col_pos-1)%4 == 0){//cp is the second number of the submatrix
sub_col_start = col_pos - 1;
sub_col_end = sub_col_start + 3;
}
else if((col_pos-2)%4 == 0){
sub_col_start = col_pos - 2;
sub_col_end = sub_col_start +3;
}

//GET THE FINAL SUB MATRIX
int a=0, b=0;
for(i=sub_row_start;i<=sub_row_end;i++){
  for(j=sub_col_start;j<=sub_col_end;j++){
  
  sub_matrix[a][b] = matrix[i][j];
  linear_search(sub_matrix[a][b], check_arr);
  //printf("%c\t", sub_matrix[a][b]);
  b++;
  }
a++;
//printf("\n");
}
 
int c = 0, pos = 0; 
for(i=0;i<16;i++){
if(check_arr[i] == 0){
c++;
pos = i;
}

//printf("%d\n",check_arr[i]); 
} 
int ch=0;
for(i=0;i<16;i++){
 if(check_arr[i] == 0){
 matrix[row_pos][col_pos] = arr[pos];
 check_arr[i] = 1;
 printf("%d\n",++ch);
 get_submatrix(matrix,row_pos,col_pos);
 }
}

/*if(c==0){
check_final_matrix(matrix,row_arr,col_arr);
}

if(c == 1){
matrix[row_pos][col_pos] = arr[pos];
check_final_matrix(sub_matrix,row_arr,col_arr);
//traverse_hexadoku(matrix, 16,16);
//printf("%c\n", arr[pos]);
}
else if(c>1){
//char c = '?';
matrix[row_pos][col_pos] = c;
solver(matrix,row_pos,col_pos,row_arr,col_arr);
//traverse_hexadoku(matrix, 16,16);
}
 
 
for(i=0;i<16;i++){
  printf("Check array: %d\n",check_arr[i]);
 }
print_matrix(matrix,16,16);
 exit(0);
 */
}

void solver(char** matrix,int row_pos,int col_pos,char* row_arr,char* col_arr){
int i;
  for(i=0;i<16;i++){
  x = i;
   if(check_arr[x]==0){
  matrix[row_pos][col_pos]=arr[x];
  traverse_hexadoku(matrix,16,16);
 printf("%c\n",arr[x]);
 }
}
 printf("\n\n");
 for(i=0;i<16;i++){
 check_arr[i] =0;
 }
 check_final_matrix(matrix,row_arr,col_arr);
}

void linear_search(char chr, int* check_arr){

int i,c;
for(i=0;i<16;i++){
 if(chr == arr[i] && check_arr[i] == 0){
 check_arr[i] = 1; 
 break;
 }
 else if(chr == arr[i] && check_arr[i] == 1){
 check_arr[i] = check_arr[i]+1;
 }
 else if(chr == arr[i] && check_arr[i] == 2){
 check_arr[i] = check_arr[i]+1;
 }
 else if(chr == arr[i] && check_arr[i] == 3){
 
 printf("no-solution\n");
 exit(0);
 }
}

}

void print_matrix(char** matrix, int row,int col){

int i,j;

/*for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 get_submatrix(matrix,i,j);
 }

}*/

for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 printf("%c\t", matrix[i][j]);
 }
printf("\n");
}
printf("\n");
//exit(0);
}

void check_final_matrix(char** sub_matrix, char* row_arr, char* col_arr){

int i,j;
int check[16];
for(i=0;i<16;i++){
check[i] = 0;
}
char chr;
for(i=0;i<16;i++){
linear_search(row_arr[i], check);
linear_search(col_arr[i],check);
}

for(i=0;i<4;i++){
 for(j=0;j<4;j++){
 linear_search(sub_matrix[i][j], check);
 }

}

}

void free_matrix(char** matrix,int row){
int i;
for(i=0;i<row;i++){
free(matrix[i]);
}

}

int main(int argc, char** argv){

char** matrix;
int row = 16;
int col = 16;
int lc, i , j;

FILE* fp = fopen(argv[1], "r");

if(fp == NULL){
exit(0);
}

/*if(fscanf(fp,"%c\t",&matrix[lc][j])==EOF){
 exit(0);
}*/

matrix = malloc(row*sizeof(char*));//allocating memory to matrix
for(i=0;i<row;i++){

matrix[i] = malloc(col*sizeof(char));

}

for(lc=0;lc<row;lc++){

 for(j=0;j<col;j++){
 
 
   fscanf(fp,"%c\t",&matrix[lc][j]);
   
   if(matrix[lc][j] == ' '){
   exit(0);
   }
   
 }
 fscanf(fp,"\n");

}
print_matrix(matrix,row,col);
traverse_hexadoku(matrix, row, col);
 
fclose(fp);

return 0;
}
