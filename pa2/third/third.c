#include <stdio.h>
#include <stdlib.h>

void display_matrix(double**,int,int);
double** calculate_w(double**,double**,int,int,int,int);
double** transpose_matrix(double** matrix, int row, int col);
double** multiply_matrices(double** matrix_1,int row_1,int col_1,double** matrix_2,int row_2,int col_2);
double** divide_row(double** matrix,int count,int row,int col,int j);
double** subtract_row(double** matrix,int count,int row,int col,int j);
double** divide_row1(double** identity_matrix,int count,int row,int col,int j);
double** subtract_row1(double** identity_matrix,int count,int row,int col,int j);
double** inverse_function(double**matrix,double** identity_matrix,int row,int col);
double** find_inverse(double**,int,int);

double fact = 0.0;

void display_matrix(double** matrix, int row, int col){  

int i,j;
for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 printf("%0.0lf\t" , matrix[i][j]);
 }
 printf("\n");
}

}

double** calculate_w(double** X1, double** Y, int x_row,int x_col,int y_row,int y_col){

int i,j;
double** X;
int col=0;
double** Xt;
double** Xi;
double** Xti;
double** Xm;
//double** identity_matrix;
double** W;
x_col+=1;
X = malloc(x_row*sizeof(double*));
for(i=0;i<x_row;i++){
X[i] = malloc(x_col*sizeof(double));
}

Xt = malloc(x_col*sizeof(double*));
for(i=0;i<x_col;i++){
Xt[i] = malloc(x_row*sizeof(double));
}

Xti = malloc(x_col*sizeof(double*));
for(i=0;i<x_col;i++){
Xti[i] = malloc(x_row*sizeof(double));
}

Xi = malloc(x_col*sizeof(double*));
for(i=0;i<x_col;i++){
Xi[i] = malloc(x_col*sizeof(double));
}

Xm = malloc(x_col*sizeof(double*));
for(i=0;i<x_col;i++){
Xm[i] = malloc(x_col*sizeof(double));
}

W = malloc(x_col*sizeof(double*));
for(i=0;i<x_col;i++){
W[i] = malloc(1*sizeof(double));
}

for(i=0;i<x_row;i++){
 X[i][0] = 1;
 col = 0;
 for(j=0;j<x_col-1;j++){
 X[i][j+1] = X1[i][col];
 col++;
}

}


Xt = transpose_matrix(X,x_row,x_col);
Xm = multiply_matrices(Xt,x_col,x_row,X,x_row,x_col);

Xi = find_inverse(Xm, x_col, x_col);

Xti = multiply_matrices(Xi,x_col,x_col,Xt,x_col,x_row);

W = multiply_matrices(Xti,x_col,x_row,Y,y_row,y_col);


for(i=0;i<x_row;i++){
free(X[i]);

}

for(i=0;i<x_col;i++){
free(Xti[i]);
free(Xi[i]);
free(Xm[i]);
free(Xt[i]);
}
return W;
}

double** find_inverse(double** matrix,int row,int col){

int i,j;
int count  = 0;
double** identity_matrix;

identity_matrix = malloc(row*sizeof(double*));//allocating memory to first matrix
for(i=0;i<row;i++){
identity_matrix[i] = malloc(col*sizeof(double));
}
//INITIALIZE IDENITY MATRIX
for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 if(i==j){
 identity_matrix[i][j] = 1;
 }
 else{
 identity_matrix[i][j] = 0;
 }
 }
}


for(i=0;i<row;i++){
 for(j=0;j<col;j++){
  if(i == j){
    count = i;
    while(count<row){
    matrix = divide_row(matrix,count,row,col,j);
    identity_matrix = divide_row1(identity_matrix,count,row,col,j);
    count++;
    }
    count = i;
   
    matrix = subtract_row(matrix,count,row,col,j);
    identity_matrix = subtract_row1(identity_matrix,count,row,col,j);
  }
 }

}

matrix = inverse_function(matrix,identity_matrix,row,col);
return matrix;
}

double** inverse_function(double**matrix,double** identity_matrix,int row,int col){

double* ptr_row;
double* prev_row;
int i,j,k,l,count=0;
double n = 0.0;

ptr_row = malloc(col*sizeof(double));
prev_row = malloc(col*sizeof(double));

for(i=row-1;i>=0;i--){
 for(j=col-1;j>=0;j--){

  if(i == j && i!=0){
  count = i;
  
   while(count>0){
   n = matrix[count-1][j];
  
   if(n == 0){
   count--;
   continue;
   }
   
   for(l=0;l<row;l++){
   ptr_row[l] = matrix[i][l];
   }
   
   for(l=0;l<row;l++){
   prev_row[l] = identity_matrix[i][l];
   }
   
   for(k=0;k<row;k++){
   matrix[count-1][k] -=   (n* ptr_row[k]);
   identity_matrix[count-1][k] -= (n*prev_row[k]);
   
   }
   
   count--;
   }
   
  }
 
 }


}

free(ptr_row);
free(prev_row);

return identity_matrix;

}


double** divide_row(double** matrix,int count,int row,int col,int x){
int j;


 fact = matrix[count][x];
 
 for(j=0;j<col;j++){
 if(fact!=0.0 || fact!=1.0){
   matrix[count][j]=matrix[count][j]/fact;
   
   }
  if(matrix[count][j] == -0.0){
  matrix[count][j] = 0.0;
  }
  
 }

return matrix;
}

double** divide_row1(double** identity_matrix,int count,int row,int col,int x){
int j;


 for(j=0;j<col;j++){
 if(fact!=0.0 || fact!=1.0){
   identity_matrix[count][j]=identity_matrix[count][j]/fact;
   
   }
  if(identity_matrix[count][j] == -0.0){
  identity_matrix[count][j] = 0.0;
  }
 }

return identity_matrix;
}

double** subtract_row(double** matrix,int count,int row,int col,int y){

int j=0;
int x= 1;

 while((count+x)<row){
 for(j=0;j<col;j++){
 matrix[count+x][j] = (matrix[count][j] - matrix[count+x][j]);
 }
 x++;
 
 }


return matrix;
}

double** subtract_row1(double** matrix,int count,int row,int col,int y){

int j=0;
int x= 1;

 while((count+x)<row){
 for(j=0;j<col;j++){
 matrix[count+x][j] = (matrix[count][j] - matrix[count+x][j]);
 }
 x++;
 
 }

return matrix;
}

double** multiply_matrices(double** matrix_1,int row_1,int col_1,double** matrix_2,int row_2,int col_2){

double** result_matrix;
int row = row_1;
int col = col_2;
int i,k,m,n;

result_matrix = malloc(row*sizeof(double*));

for(i=0;i<row_1;i++){

result_matrix[i] = malloc(col*sizeof(double));

}

  int rc=0,cc=0;
  
  m = 0;n = 0;
  
  while(m <row_1 && n<col_2){//evry row and column incrementation
  
  double sum=0; 
  
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
  
return result_matrix;


}//end of function


double** transpose_matrix(double** matrix, int x_row, int x_col){
 
 double** X;
 int i,j;
 int col = x_row;
 int row = x_col;

 X = malloc(row*sizeof(double*));
for(i=0;i<row;i++){
X[i] = malloc(col*sizeof(double));
}

 for(i=0;i<row;i++){
 for(j=0;j<col;j++){
 X[i][j] = matrix[j][i];
 }
}
return X;
}

int main(int argc, char** argv){

double** attributes;
double** house_price;
double** W;
int a_row = 0; 
int a_col = 0;
int i,j;
int lc = 0;
FILE* fp = fopen(argv[1],"r");

if(fp == NULL){
exit(0);
}

if(fscanf(fp,"%d\n", &a_col) == EOF){
exit(0);
}

fscanf(fp,"%d\n",&a_row);

W = malloc((a_col+1)*sizeof(double*));

for(i=0;i<(a_col+1);i++){
W[i] = malloc(1*sizeof(double));
}

//INITIALIZE MATRICES
attributes = malloc(a_row*sizeof(double*));

for(i=0;i<a_row;i++){
attributes[i] = malloc(a_col*sizeof(double));
}

house_price = malloc(a_row*sizeof(double*));
for(i=0;i<a_row;i++){
house_price[i] = malloc(1*sizeof(double)); 
}

for(lc=0;lc<a_row;lc++){

 for(j=0;j<=a_col;j++){
 
   if(j==a_col){
    fscanf(fp,"%lf\n", &house_price[lc][0]);
    
    continue;
   }
   fscanf(fp,"%lf,", &attributes[lc][j]);
 }

}

fclose(fp);

W = calculate_w(attributes,house_price,a_row,a_col,a_row,1);

for(i=0;i<a_row;i++){
free(attributes[i]);
free(house_price[i]);
}

double** final_X;
double** temp_X;
double** ans;
FILE* fp1 = fopen(argv[2],"r");

a_col+=1;

if(fp1 == NULL){
exit(0);
}

if(fscanf(fp1,"%d\n", &a_row) == EOF){
exit(0);
}

final_X = malloc(a_row*sizeof(double*));

for(i=0;i<a_row;i++){
final_X[i] = malloc(a_col*sizeof(double));
}

temp_X = malloc(a_row*sizeof(double*));

for(i=0;i<a_row;i++){
temp_X[i] = malloc((a_col-1)*sizeof(double));
}

ans = malloc(a_col*sizeof(double*));

for(i=0;i<a_col;i++){
ans[i] = malloc(1*sizeof(double));
}

for(lc=0;lc<a_row;lc++){
 for(j=0;j<a_col-1;j++){
   fscanf(fp1,"%lf,", &temp_X[lc][j]);
 }
}

int col = 0;
for(i=0;i<a_row;i++){
 final_X[i][0] = 1;
 col = 0;
 for(j=0;j<a_col-1;j++){
 final_X[i][j+1] = temp_X[i][col];
 col++;
}

}

ans = multiply_matrices(final_X,a_row,a_col,W,a_col,1);
display_matrix(ans,a_row,1);


for(i=0;i<a_row;i++){
free(final_X[i]);
free(temp_X[i]);
free(ans[i]);

}

for(i=0;i<a_col;i++){
free(W[i]);
}

fclose(fp1);
return 0;
}
