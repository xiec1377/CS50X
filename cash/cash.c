#include <cs50.h> //to get get_float function
#include <math.h> //to get "round" function
#include <stdio.h>

int main(void)
{
    float cash; 
    int cents, coins = 0, coins_added = 0; //declare and initialize variables
    do
    {
        cash = get_float("Change owed: "); //prompts user, sets cash variable
    }
    while (cash < 0); //keep prompting given the condition
    cents = round(cash * 100); //convert dollars into cents
    while (cents / 25 > 0) //check for quarters
    {
        coins_added = cents / 25; 
        cents -= coins_added * 25;
        coins += coins_added;
    }
    while (cents / 10 > 0) //check for dimes
    {
        coins_added = cents / 10;
        cents -= coins_added * 10; 
        coins += coins_added;
    }
    while (cents / 5 > 0) //check for nickels
    {
        coins_added = cents / 5;
        cents -= coins_added * 5;
        coins += coins_added;
    }
    coins_added = cents; //check for pennies
    cents -= coins_added;
    coins += coins_added;
    printf("%i\n", coins); //print least coins given as change
}
