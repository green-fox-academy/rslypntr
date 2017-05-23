#include <stdio.h>
#include <stdlib.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, its size and its new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */

 int *resize(int *array, int size, int new_size);

int main()
{
    //creating a test array with malloc
    int *test_array = (int*) malloc(3* sizeof(int));
    for(int i = 0; i < 3; i++) {
        test_array[i] = i + 2;
    }


    //testing the resize() function
    int *test_result = resize(test_array, 3, 6);
    for(int j = 0; j < 6; j++) {
        printf("%d\t", test_result[j]);
    }

    return 0;
}

int *resize(int *array, int size, int new_size)
{
    if( new_size < size) {
        printf("Invalid parameters.");
        return 0;
    } else {
        int *result = (int*) calloc(new_size, sizeof(int));
        for(int i = 0; i < size; i++) {
            result[i] = array[i];
        }
        return result;
        free(array);
    }


}
