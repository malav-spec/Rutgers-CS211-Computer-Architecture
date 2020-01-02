#include <stdio.h>
#include <stdlib.h>

void display_matrix(int**, int, int);
void multiply_matrices(int** matrix_1,int row_1,int col_1,int** matrix_2,int row_2,int col_2);
void free_matrix(int** matrix,int row,int col);

void multiply_matrices(int** matrix_1,int row_1,int col_1,int** matrix_2,int row_2,int col_2){

int** result_matrix;
int row = row_1;
int col = col_2;
int i,j,k,l,m,n,x;

result_matrix = malloc(row*sizeof(int*));

for(i=0;i<row_1;i++){

result_matrix[i] = malloc(col*sizeof(int));

}

  int rc=0,cc=0;
  
  m = 0;n = 0;
  
  while(m <row_1 && n<col_2){//evry row and column incrementation
  
  int sum=0; 
  
   for(k=0;k<col_1;k++){
    
    sum = sum + (matrix_1[m][k]*matrix_2[k][n]);
    
      } 
      
    result_matrix[rc][cc] = sum;
      
    if(n<col_2){
     n++;
     cc++;
      
      if(n == col_2){
       m++;
       n=0;
       rc++;
       cc=0;
      }
   
    }
   
  }//end while
  
display_matrix(result_matrix, row_1,col_2);


}//end of function

void display_matrix(int ** matrix,int rows,int cols){

int i,j;

for(i=0;i<rows;i++){
  for(j=0;j<cols;j++){
  printf("%d\t",matrix[i][j]);
  }
  printf("\n");
 } 
 
}

void free_matrix(int** matrix,int row,int col){

int i,j;
for(i=0;i<row;i++){

 free(matrix[i]);
}

free(matrix);
}

int main(int argc, char** argv){

int** matrix_1;
int** matrix_2;
int row_1 = 0,col_1 = 0;
int row_2 = 0,col_2 = 0;
int i,j;
int lc=0;


FILE* fp = fopen(argv[1],"r");

if(fp == NULL){
exit(0);
}

if(fscanf(fp,"%d\t%d\n",&row_1,&col_1)==EOF){
 exit(0);
}



matrix_1 = malloc(row_1*sizeof(int*));//allocating memory to first matrix
for(i=0;i<row_1;i++){

matrix_1[i] = malloc(col_1*sizeof(int));

}

for(lc=0;lc<row_1;lc++){

 for(j=0;j<col_1;j++){
 
   fscanf(fp,"%d\t",&matrix_1[lc][j]);
   
 }
 fscanf(fp,"\n");

}

if(fscanf(fp,"%d\t%d\n",&row_2,&col_2)==EOF){
 exit(0);
}

matrix_2 = malloc(row_2*sizeof(int*));//allocate memory for matrix 2

for(i=0;i<row_2;i++){

matrix_2[i] = malloc(col_2*sizeof(int));

}

 
for(lc=0;lc<row_2;lc++){
 for(j=0;j<col_2;j++){
 
  fscanf(fp,"%d\t",&matrix_2[lc][j]);
   }
   fscanf(fp,"\n");
 }
 
 fclose(fp);
 
 if(col_1 != row_2){
 
 printf("bad-matrices\n");
 exit(0);
 
 }

multiply_matrices(matrix_1,row_1,col_1,matrix_2,row_1,col_2);
free_matrix(matrix_1,row_1,col_1);
free_matrix(matrix_2,row_2,col_2);


return 0;
}
