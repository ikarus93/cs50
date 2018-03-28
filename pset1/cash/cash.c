//Implement a program that calculates the minimum number of coins required to give a user change.


#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    float change;
    do //verifying user input is non negative
    {
        change = get_float("Cash: ");
    }
    while (change < 0);


    int casted = round(change * 100);   //changing float to int
    int coins = 0;

    while (casted > 0)
    {
        coins ++;          //increment coins returned
        if (casted >= 25)
        {
            casted -= 25;
        }
        else if (casted >= 10)
        {
            casted -= 10;
        }
        else if (casted >= 5)
        {
            casted -= 5;
        }
        else
        {
            casted -= 1;
        }
    }
    printf("%i\n", coins);         //return coins
}