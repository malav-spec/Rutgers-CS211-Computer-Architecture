#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrimeNumber(int n);
bool isRightTrunc(int n);

int main(int argc, char** argv){

int num=0;

FILE* fp = fopen(argv[1],"r");

if(fp== NULL){
exit(0);
}

if(fscanf(fp,"%d\n",&num)==EOF){
exit(0);
}

int i;
for(i=0;i<num;i++){
int temp;

fscanf(fp,"%d\n",&temp);

bool ans = isRightTrunc(temp);

if(ans == true){
printf("yes\n");
}
else
{
printf("no\n");
}

}

fclose(fp);

return 0;
}

bool isRightTrunc(int n){

if(n == 0){

return false;
	}
	
if(n == 1){
return true;
}

int x = n;

bool isPrime;

while(x>0){

isPrime = isPrimeNumber(x);

if(isPrime == true){

x=x/10;

  }

else{

return false;

   } 

  }
  return true;
}

bool isPrimeNumber(int n){

int a = n;
int i,c=0;

if(n == 1){
return true;
}

for(i=1; i<=a;i++){

if(a%i== 0){

 c=c+1;

   }
 

 }
 
if(c==2){

return true;
   }

return false;

}


