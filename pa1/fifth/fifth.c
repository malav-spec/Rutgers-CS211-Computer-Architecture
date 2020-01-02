#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void display_matrix(int**, int, int);
void check_duplicate(int**,int,int);
int column_sum(int**, int);
int row_sum(int**, int);
int diagonal_sum(int**, int);


int diagonal_sum(int** matrix, int row){

int i ,j,l_sum = 0,r_sum = 0;

for(i=0;i<row;i++){

  l_sum += matrix[i][i];
  
  }
  
int c = row-1;
for(i=0;i<row;i++){

r_sum += matrix[i][c];
c--;
  }
 
  
  if(r_sum != l_sum){
  return 0;  
  }
  
  return (l_sum*row);
}

int row_sum(int** matrix, int row){

int i=0,j,sum=0,sum1=0;

while(i<row){
  
  for(j=0;j<row;j++){
  
  sum = sum + matrix[i][j];
  
    }
 // printf("%d ", sum);
   i++;
   
   if(i<row){ 
    
    for(j=0;j<row;j++){
  
     sum1 = sum1 + matrix[i][j];
    }
     //printf("%d ", sum1);
    
    if(sum != sum1){
     return 0;
     }
     sum = 0;
   sum1 = 0;
   }// end of if
   
   
 }//end of while
  
return (sum*row);

}

int column_sum(int** matrix, int row){

int i=0,j,sum=0,sum1=0;

while(i<row){
  
  for(j=0;j<row;j++){
  
  sum = sum + matrix[j][i];
   //printf("%d ", sum);
    }
   i++;
   
   if(i<row){ 
    
    for(j=0;j<row;j++){
  
     sum1 = sum1 + matrix[j][i];
  //    printf("%d ", sum1);
    }
    
    if(sum != sum1){
    
    return 0;
    }
    sum = 0;
   sum1 = 0;
   }
   
    
  }
  
 
  return (sum*row);
}


void check_duplicate(int** matrix,int rows,int cols){

int i,j;

int size = rows*rows;
int* matrix_1 = malloc(size*sizeof(int));

int k=0;
 
for(i=0;i<rows;i++){
 
 for(j=0;j<cols;j++){
 
  matrix_1[k] = matrix[i][j]; 
  k++;
  
  }
 
 }
 

//sort in ascending order

int temp;

for(i=0;i<size-1;i++){
  for(j=i+1;j<size;j++){
   if(matrix_1[i]>=matrix_1[j]){
   
      temp = matrix_1[i];
      matrix_1[i]=matrix_1[j];
      matrix_1[j]=temp;
        }
     }
     
  }

int a,b;
for(i=0;i<size;i++){

a=matrix_1[i];
b=matrix_1[i+1];

if(i == size-1){
continue;
}
  if(a == b){
  printf("not-magic\n");
  exit(0);
  }
 
 }
  
  
}


void display_matrix(int ** matrix,int rows,int cols){

int i,j;

for(i=0;i<rows;i++){
  for(j=0;j<cols;j++){
  printf("%d\t",matrix[i][j]);
  }
  printf("\n");
 } 
  

}

int main(int argc, char** argv){

int** matrix;
int col=0,row=0;
int i,j,lc;
int arr;

FILE* fp = fopen(argv[1],"r");

if(fp == NULL){
exit(0);
}

if(fscanf(fp,"%d",&row)==EOF){
 exit(0);
}

col = row;

int size = (row*row);

matrix = malloc(row*sizeof(int*)); 

//allocating memory to first matrix



for(i=0;i<row;i++){

matrix[i] = malloc(col*sizeof(int));

}

for(lc=0;lc<row;lc++){

 for(j=0;j<col;j++){
 
   fscanf(fp,"%d\t",&matrix[lc][j]);
   
  /* if(row == 1 && matrix[lc][j] == 1){
    printf("magic\n");
    return 0;
    }   */
    
   if(matrix[lc][j] < 1){
   printf("not-magic");
   exit(0);
   }
 }
 
 fscanf(fp,"\n");
}
 
 int col_sum;
 int r_sum;
 int d_sum;

 
 check_duplicate(matrix,row,col);
 col_sum = column_sum(matrix,row);
 r_sum = row_sum(matrix,row);
 d_sum = diagonal_sum(matrix,row);
 
 /*printf("%d\n", r_sum);
 printf("%d\n", col_sum);
 printf("%d\n", d_sum);*/
 
 if(col_sum == 0 || r_sum == 0 || d_sum == 0){
 
 printf("not-magic\n");
 
 }
 
 else{
 printf("magic\n");
 }

return 0;
}
