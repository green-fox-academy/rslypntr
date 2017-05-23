#include <stdio.h>
#include <string.h>

struct pirate {
    char name[256];
    int has_wooden_leg;
    short int gold_count;
};

// TODO:
// Create a function that takes an array of pirates (and its length) then returns the sum of the golds of all pirates

// TODO:
// Create a function that takes an array of pirates (and its length) then returns the average of the gold / pirate

// TODO:
// Create a function that takes an array of pirates (and its length) then returns the name of the
// richest that has wooden leg

int goldsum(struct pirate prts[], int len);
float goldavg(struct pirate prts[], int len);
char *richest_wleg(struct pirate prts[], int len);

int main()
{
    struct pirate pirates[] = {
        {"Jack", 0, 18},
        {"Uwe", 1, 8},
        {"Hook", 1, 12},
        {"Halloween kid", 0, 0},
        {"Sea Wolf", 1, 14},
        {"Morgan", 0, 1}
    };
    printf("Sum of golds: %d\n", goldsum(pirates, 6));
    printf("Average gold per pirate: %.2f\n", goldavg(pirates, 6));
    printf("The richest pirate with a wooden leg: %s\n", richest_wleg(pirates, 6));



    return 0;
}

int goldsum(struct pirate prts[], int len)
{
    int sum = 0;
    for(int i = 0; i < len; i ++) {
        sum += prts[i].gold_count;
    }
    return sum;
}

float goldavg(struct pirate prts[], int len)
{
    int sum = goldsum(prts, len);
    float avg = (float) sum / len;
    return avg;

}

char *richest_wleg(struct pirate prts[], int len)
{
    int mostgold = prts[0].gold_count;
    int index =0;
    for(int i = 0; i < len; i++) {
        if(prts[i].gold_count > mostgold && prts[i].has_wooden_leg == 1) {
            mostgold = prts[i].gold_count;
            index = i;
        }
    }
    return prts[index].name;


}
