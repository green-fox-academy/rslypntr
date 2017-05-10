#include <stdio.h>

/* Write a non void function which has a paramters (let's say for example x).
The funtion than returns the "xth" fibonaci number.
What the hack is a fibonacci number? Search it on wikipedia!
*/
int fibonacci(int x);

int main(){
    int i;
    for(i=0; i<20; i++){
        printf("%d\n", fibonacci(i));
    }

    return 0;
}

int fibonacci(int x){
    if(x==0){
        return 0;
    }
    if(x==1){
        return 1;
    }
    else{
        return fibonacci(x-1)+ fibonacci(x-2);
    }
}
