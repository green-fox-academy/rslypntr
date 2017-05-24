#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {MATH, HISTORY, ENGLISH, SCIENCE} subject_t;

typedef struct {
    subject_t subject;
    int value;
} grade_t;

typedef struct {
    char name[128];
    int age;
    grade_t* grades;
    int grade_count;
} student_t;

// TODO:
// Create a function the constructs a Student (returns a pointer to a new student)
// It should take her name and age as parameter
// It should allocate 5 grades
// It should set the grade_count to 0

student_t *student_constructor(char *name, int age);

// TODO:
// Create a function that takes 3 parameters:
// A pointer to a Student
// A Subject
// An int (1-5)
// It should set the last grade's values with the given arguments
void set_grade(student_t *student, subject_t subj, int grd);

// TODO:
// Create a function that takes a Student as a pointer and returns the subject
// that the student has worst grade in
subject_t worst_grade(student_t *student);

// TODO:
// Create a function that deconstructs a Student
// It should take a pointer that points to the student
// It should free each Grade and the Student itself
void student_deconstructor(student_t *student);

int main()
{
    student_t *test_student = student_constructor("Aladar", 15);
    printf("Name: %s\n", test_student->name);
    printf("Age: %d\n", test_student->age);
    printf("Grade count: %d\n", test_student->grade_count);
    set_grade(test_student, MATH, 4);
    set_grade(test_student, ENGLISH, 4);
    set_grade(test_student, SCIENCE, 5);
    set_grade(test_student, HISTORY, 2);
    for (int i = 0; i < 3; i++) {
        printf("%d\t", test_student->grades[i].value);
    }
    printf("\nWorst grade in subject: ");
    switch(worst_grade(test_student)){
    case MATH:
        printf("Math\n");
        break;
    case HISTORY:
        printf("History\n");
        break;
    case ENGLISH:
        printf("English\n");
        break;
    case SCIENCE:
        printf("Science\n");
        break;
    }
    student_deconstructor(test_student);
    printf("Name: %s\n", test_student->name);
    printf("Age: %d\n", test_student->age);
    printf("Grade count: %d\n", test_student->grade_count);

    return 0;
}

student_t *student_constructor(char *name, int age)
{
    student_t *student_ptr = (student_t*) malloc(sizeof(student_t)); // question malloc vs calloc
    strcpy(student_ptr->name, name);
    student_ptr->age = age;
    grade_t *grade_set = (grade_t*) calloc(5, sizeof(grade_t));
    student_ptr->grades = grade_set;
    return student_ptr;
}

void set_grade(student_t *student, subject_t subj, int grd)
{
   student->grades[student->grade_count].subject = subj;
   student->grades[student->grade_count].value = grd;
   student->grade_count++;
}

subject_t worst_grade(student_t *student)
{
    int w_grade = student->grades[0].value;
    subject_t w_subj = student->grades[0].subject;
    for (int i =0; i < student->grade_count; i++) {
        if (student->grades[i].value < w_grade) {
            w_subj = student->grades[i].subject;
            w_grade = student->grades[i].value;
        }
    }
    return w_subj;
}

void student_deconstructor(student_t *student)
{
    free(student->grades);
    free(student);
}
