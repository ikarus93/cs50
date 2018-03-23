//Retrieves amount of coins needed to change users cash

#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    float change = get_float("Cash: ");

    while (change < 0)
        //verifying user input is non negative
    {
        change = get_float("Cash ");
    }

    int casted = round(change * 100);   //changing float to int
    int coins = 0;

    while (casted > 0)
    {
        coins ++;
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
    printf("%i\n", coins);
}