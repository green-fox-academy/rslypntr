#ifndef _TODO_H_
#define _TODO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************
 *STRUCTURES
 ***************/

typedef struct {
    char description[256];

}item_t;

typedef struct {
    item_t *array;
    int len;
} list_t;


/***************
 *FUNCTIONS
 ***************/


/****************
 *Print menu
 ****************/
void print_menu()
{
    char buffer[255];
    FILE *fp;
    fp = fopen("startup_info.txt", "r");
    fgets(buffer, 255, fp);
    while(!feof(fp)) {
        printf("%s", buffer);
        fgets(buffer, 255, fp);
    }
    fclose(fp);
}

/****************
 *Initialize list
 ****************/
list_t *list_init()
{
    list_t *list = (list_t*) malloc(sizeof(list_t));
    list->array = NULL;
    list->len = 0;
    return list;
}

/****************
 *Add item to list
 ****************/
void add_task(list_t *list, char *description)
{
    if (strcmp(description, "") == 0) {
        printf("Unable to add: No task is provided\n");
    } else {
        int new_len = list->len + 1;
        list->array = realloc(list->array, sizeof(item_t) * new_len);
        list->len = new_len;
        strcpy(list->array[new_len - 1].description, description);
    }
}

/****************
 *List items
 ****************/
void list_tasks(list_t *list)
{
    printf("List by number\n");
    printf("====================\n");
    printf("Num | Tasks\n");
    for (int i = 0; i < list->len; i++) {
        printf("%d -\t%s\n", i+1, list->array[i].description);
    }
}

/****************
 *Write to file
 ****************/
void write_to_file(list_t *list, char *fname)
{
    char filename[255];
    strcpy(filename, fname);
    FILE *fp;
    fp = fopen(filename, "w");
    fputs("List by number\n", fp);
    fputs("====================\n", fp);
    fputs("Num | Tasks\n", fp);
    for (int i =0; i < list->len; i++) {
        fprintf(fp, "%d  -\t%s\n", i+1, list->array[i].description);
    }
    fclose(fp);
}

/****************
 *Read from file
 ****************/
void read_from_file (list_t *list, char *fname)
{
    char filename[255];
    strcpy(filename, fname);
    char buffer[255];
    FILE *fp;
    fp = fopen(filename, "r");
    printf("Reading from file: \n");
    for (int i = 0; i < 3; i++) {
        fgets(buffer, 255, fp);
    }
    char description[255];
    fgets(buffer, 255, fp);
    while(!feof(fp)) {
            strtok(buffer, "\t");
            strcpy(description, strtok(NULL, " \n"));
            add_task(list, description);
            fgets(buffer, 255, fp);
    }

    fclose(fp);
}

/****************
 *Empty the list
 ****************/
list_t *empty_list(list_t *list)
{
    free(list);
    list_t *newlist = list_init();
    printf("No todos for today! :)\n");
    return newlist;
}

/**********************
 *Remove item from list
 **********************/
void remove_task(list_t *list, char *index)
{   if (strcmp(index,"") == 0) {
        printf("Unable to remove: No index is provided\n");
    } else if (atoi(index) > list->len) {
        printf("Unable to remove: Index is out of bound\n");
    } else if (atoi(index) == 0) {
        printf("Unable to remove: Index is not a number\n");
    } else {
        int ind = atoi(index) - 1;
        for(int i = ind; i < list->len - 1; i++) {
            list->array[i] = list->array[i + 1];
        }
        list->len--;
        list->array = realloc(list->array, sizeof(item_t) *list->len);
    }
}

/********************************
 *Get instruction from user input
 ********************************/
char *get_instruction(char *input)
{
    char *instruction = strtok(input, " ");
    return instruction;
}

/************************************
 *Get instruction argument user input
 ************************************/
char *get_description(char *input)
{
    char *desc = strtok(NULL, "\n");
    return desc;
}

/********************************
 *Execute commands
 ********************************/
void command_execution(char *instruction, char *input, list_t *list)
{
    char description[255];
    if(strcmp(instruction, "-a") == 0) {
            strcpy(description, get_description(input));
            add_task(list, description);
    } else if (strcmp(instruction, "-l") == 0) {
            list_tasks(list);
    } else if (strcmp(instruction, "-wr") == 0) {
            strcpy(description, get_description(input));
            write_to_file(list, description);
    } else if (strcmp(instruction, "-rd") == 0) {
            strcpy(description, get_description(input));
            read_from_file(list, description);
    } else if (strcmp(instruction, "-e") == 0) {
            empty_list(list);
    } else if (strcmp(instruction, "-r") == 0) {
        strcpy(description, get_description(input));
        remove_task(list, description);
    } else {
        printf("\nInvalid input. Please select from the below list.\n\n");
        print_menu();

    }
}

#endif // _TODO_H_
