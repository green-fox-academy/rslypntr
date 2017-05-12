#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char word1[255];
char word2[255];

void is_anagram(char a[], char b[]);
char sort(char d[]);

int main()
{
    printf("Please enter a word:\n");
    scanf("%s", word1);
    printf("Please enter another word:\n");
    scanf("%s", word2);
    sort(word1);
    sort(word2);
    is_anagram(word1, word2);

    return 0;
}


void is_anagram(char a[], char b[]){

      if(strlen(a) == strlen(b)){
        if(strcmp(a, b)== 0){
            printf("Anagrams, yeah!\n");
        }
        else{
            printf("Not anagrams, sorry\n");
        }

    }
    else{
        printf("Not anagrams\n");
    }
}



char sort(char d[]){
    char temp;
    int d_size = strlen(d);

    for(int i=0;i<d_size-1;i++){
        for(int j=0;j<d_size-i-1;j++){
            if(d[j]>d[j+1]){
                temp=d[j];
                d[j]=d[j+1];
                d[j+1]=temp;
            }
        }
    }
    return d;
}
