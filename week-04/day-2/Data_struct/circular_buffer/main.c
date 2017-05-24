#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a struct called CircularBuffer
// It should store:
// A pointer that points to the start of a dynamically allocated array of ints (could be null) (head pointer)
// A pointer that points to the end of the dynamically allocated array of ints (could be null) (tail pointer)
// A pointer that points to the currently readable buffer item (could be null) (read pointer))
// A pointer that points to the currently writable buffer item (could be null) (write pointer)
// The length of the buffer

typedef struct CircularBuffer{
    int *head;
    int *tail;
    int *read;
    int *write;
    int *tail2;
    int len;
}cbuff;

// TODO:
// Create a function that returns a dynamically allocated CircularBuffer
//(the buffer itself should be allocated as well, not just the array inside)
// It should take a normal array and its length as argument, and it should fill all the buffer values from the array

cbuff *cbuffer_constructor(int *array, int len);


// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer
//and change that buffer's length and reallocate its array as well. (copying its values)

void resize(cbuff *cbuffer, int new_len);

// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer
//that only contains the even numbers from the old CircularBuffer

cbuff *even_cbuff(cbuff *cbuffer);

// TODO:
// Try all the functions in the main function, please deallocate any buffer and the array inside it after using them

int main()
{
    int test_array[] = {1, 3, 4, 6, 9, 8, 10, 2};
    cbuff *test_buffer = cbuffer_constructor(test_array, 8);
    printf("head: %d\n", test_buffer->head);
    printf("tail: %d\n", test_buffer->tail);
    printf("read: %d\n", test_buffer->read);
    printf("write: %d\n", test_buffer->write);
    printf("length: %d\n", test_buffer->len);
    test_buffer->read = test_buffer->head + 2;
    test_buffer->write = test_buffer->head + 1;
    printf("test (read - head): %d\n", test_buffer->read - test_buffer->head);
    printf("test (write - head): %d\n", test_buffer->write - test_buffer->head);

    cbuff *even_testbuff = even_cbuff(test_buffer);
    printf("Testing even buffer:\n");
    for (int i = 0; i < even_testbuff->len; i++) {
        printf("%d\t", *even_testbuff->read);
        even_testbuff->read++;
    }

    resize(test_buffer, 10);
    printf("\nresized head: %d\n", test_buffer->head);
    printf("resized tail: %d\n", test_buffer->tail);
    printf("resized read: %d\n", test_buffer->read);
    printf("resized write: %d\n", test_buffer->write);
    printf("resized length: %d\n", test_buffer->len);
    printf("test resized (read - head): %d\n", test_buffer->read - test_buffer->head);
    printf("test resized (write - head): %d\n", test_buffer->write - test_buffer->head);


    free(test_array);
    free(test_buffer);
    printf("head after free: %d\n", test_buffer->head);
    printf("tail after free: %d\n", test_buffer->tail);

    return 0;
}

cbuff *cbuffer_constructor(int *array, int len)
{
   int *buffer = (int*) calloc(len, sizeof(int));
   memcpy(buffer, array, len*sizeof(int));
   cbuff *result = (cbuff*) malloc(sizeof(cbuff));
   result->head = buffer;
   result->read = buffer;
   result->write = buffer;
   result->tail = buffer + (len - 1);
   result->len = len;
   return result;
}


void resize(cbuff *cbuffer, int new_len)
{
    int read_position = (cbuffer->read) - (cbuffer->head);
    int write_position = (cbuffer->write) - (cbuffer->head);
    cbuffer->head = realloc(cbuffer->head, new_len * sizeof(int));
    cbuffer->tail = (cbuffer->head) + (new_len - 1);
    cbuffer->read = (cbuffer->head) + read_position;
    cbuffer->write = (cbuffer->head) + write_position;
    cbuffer->len = new_len;
}

cbuff *even_cbuff(cbuff *cbuffer)
{
    int even_len = 0;
    cbuffer->read = cbuffer->head;
    for (int i = 0; i < cbuffer->len; i++) {
        if (*(cbuffer->read) % 2 == 0) {
            even_len++;
        }
        cbuffer->read++;
    }
    int even_array[even_len];
    cbuffer->read = cbuffer->head;
    int i = 0;
    while (i < even_len) {
        for (int j = 0; j < cbuffer->len; j++) {
                if (*(cbuffer->read) % 2 == 0) {
                    even_array[i] = *(cbuffer->read);
                    i++;
                }
                cbuffer->read++;
        }
    }
    cbuff *even_buffer = cbuffer_constructor(even_array, even_len);
    return even_buffer;

}
