#include <stdio.h>

enum car_type {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct car {
    enum car_type type;
    double km;
    double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all its stats
// If the car is a Tesla it should not print its gas level

void carstats(struct car c);

int main()
{
    struct car testcar = {
        TESLA,
        1000,
        20
    };
    carstats(testcar);
    return 0;
}

void carstats(struct car c)
{
    switch(c.type){
    case 0:
        printf("%s", "VOLVO\n");
        break;
    case 1:
        printf("%s", "TOYOTA\n");
        break;
    case 2:
        printf("%s", "LAND_ROVER\n");
        break;
    case 3:
        printf("%s", "TESLA\n");
        break;
    }
    printf("Km: %f\n", c.km);
    if(c.type != TESLA) {
        printf("%f\n", c.gas);
    }
}
