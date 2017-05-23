#include <stdio.h>

// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters


struct house{
    char address[256];
    int price;
    int rooms;
    float area;
};

// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from its area)

// TODO:
// Create a function that takes an array of houses (and its length), and counts the
// houses that are worth to buy.

int buy_decide(struct house *hs1);
int houses_to_buy(struct house houses[], int len);

int main()
{
    struct house house1 = {
        "1111 Krusper u 5",
        5000,
        3,
        10,
    };
    struct house house2 = {
        "1117, Budapest, Irinyi Jozsef utca 42.",
        1,
        288,
        12568
    };
    struct house house3 = {
        "1234, Az, Utca utca 23.",
        100,
        2,
        40
    };
    struct house house_array[3];
    house_array[0]=house1;
    house_array[1]=house2;
    house_array[2]=house3;


    if(buy_decide(&house1) == 1) {
        printf("Buy this house!\n");
    } else {
        printf("Do not buy this house!\n");
    }
    printf("Houses worth buying: %d\n", houses_to_buy(house_array, 3));
    return 0;
}

int buy_decide(struct house *hs1)
{
    if( hs1->price < hs1->area * 400) {
        return 1;
    }else {
        return 0;
    }
}

int houses_to_buy(struct house houses[], int len)
{
    int count = 0;
    for(int i =0; i < len; i++) {
        if(buy_decide(&houses[i]) == 1)
            count++;
    }
    return count;
}

