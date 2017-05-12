#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char word1[255];
char result[255];

char create_palindrome(char a[]);


int main()
{
  printf("Please enter a word:\n");
  scanf("%s", word1);
  printf("We built a palindrome for you: \n");
  create_palindrome(word1);


    return 0;
}



char create_palindrome(char a[]){

    for(int i=0;i<strlen(a); i++){
        result[i] = a[i];
  }
    for(int j=strlen(a); j<2*strlen(a); j++){
        result[j]=a[2*strlen(word1)-j-1];
  }
  printf("%s", result);
}

