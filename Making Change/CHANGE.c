#include "CHANGE.h"

#define centsinadollar 100.0
#define roundingnumber 0.5 //used to insure the number converted to int is done so correctly
#define MXN 100
#define invalid 0.00
#define roundingconstant 5

float roundingcost(float cost) {
    int cost_in_cents = (int)(cost * centsinadollar + 0.5); // converting dollars to cents in integer
    int remainder = cost_in_cents % roundingconstant; // finding the remainder after dividing by five

    if (remainder <= 2) {
        cost_in_cents = cost_in_cents - remainder; // rounding down
    }
    else if (remainder >= 3 && remainder <= 4) {

        cost_in_cents = cost_in_cents + (roundingconstant - remainder); // rounding up
    }

    return cost_in_cents / (float)centsinadollar; // converting back to dollars(float from cents
}

void calculateChange(float cost, float paid) {

    int dollars, cents;
    int notes[] = { 20, 10, 5, 2, 1 };
    int coins[] = { 25, 10, 5 };
    float change;
    int x = 0;

    change = paid - cost;
    dollars = (int)change;
    cents = (int)((change - dollars) * centsinadollar);// converting dollars to cents

    printf("%.2f %.2f\n", cost, paid);


    for (x = 0; x < 5; x++) { // printing dollar notes
        int count = dollars / notes[x];
        if (count > 0) {
            printf("$%d*%d ", notes[x], count);
            dollars -= count * notes[x];
        }
    }

    for (int i = 0; i < 3; i++) { // printing the coins
        int count = cents / coins[i];
        if (count > 0) {
            printf("%dc*%d ", coins[i], count);
            cents -= count * coins[i];
        }
    }

    printf("\n");
}

void finaldecision(float cost, float paid, float rounded_cost) {

    printf("%.2f %.2f\n", cost, paid);

    if (paid < rounded_cost) {
        printf("Not enough money offered.\n");
    }
    else if (paid == rounded_cost) {
        printf("Exact amount.\n");
    }
    else {
        double change = paid - rounded_cost;
        calculateChange(cost, paid); //returns(prints) the amount of change in bills and coins
    }
}