#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function that takes a double array as a parameter, and the length of the array.
// This function should calculate the avarage of the elements.

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It calculates how much elements are under the avarage, and returns with that.

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It allocates a new array, and loads into it the elements which are under the average.
// It returns a pointer to the new array.

double elements_avg(double array[], int len);
int under_avg_count(double array[], int len);
double *under_avg_list(double array[], int len);

int main()
{
    double test_array[] = {1.03, 45.67, 43.2444, 16.5556, 897.3, 12, 2.245, 1000, 150.3};
    printf("Average of elements: %f\n", elements_avg(test_array, 9));
    printf("Number of elements below average: %d\n", under_avg_count(test_array, 9));

    double *test_result = under_avg_list(test_array, 9);
    int test_size = under_avg_count(test_array, 9);
    printf("%d", test_size);
    printf("\nNew array containing elements below average:\n");
    for(int i = 0; i < test_size; i++) {
        printf("%f\t", test_result[i]);
    }


    return 0;
}

double elements_avg(double array[], int len)
{
    int sum = 0;
    for(int i = 0; i < len; i++) {
        sum += array[i];
    }
    double avg = sum / len;
    return avg;

}

int under_avg_count(double array[], int len)
{
    double avg = elements_avg(array, len);
    int count = 0;
    for(int i = 0; i < len; i ++) {
        if(array[i] < avg){
            count++;
        }
    }
    return count;
}

double *under_avg_list(double array[], int len)
{
    double avg = elements_avg(array, len);
    int count = under_avg_count(array, len);
    double *result = (double*) malloc(count * sizeof(double)); //typecasting question!
    int i = 0;
    while(i < sizeof(result)) {
        for(int j = 0; j < len; j++){
            if(array[j] < avg) {
                result[i] = array[j];
                i++;
            }
        }
    }
    return result;
}
