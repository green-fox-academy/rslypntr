#include <stdio.h>
#include <string.h>
#include <string.h>

int is_palindrom(char *a);

int main()
{
	char original_string[100];
	printf("Enter the string to check if it is a palindrome\n");
	gets(original_string);

	if (is_palindrom(original_string)) {
            printf("palindrome!\n");
    } else {
        printf("not palindrome\n");
    }
	return 0;
}

int is_palindrom(char *a)
{

	char b[100];
	strcpy(b, a);
	strrev(b);

	if (strcmp(a, b) == 0)
		return 1;
	else
		return 0;
}
