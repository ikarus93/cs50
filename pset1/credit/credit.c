//Implement a program that determines whether a provided credit card number is valid according to Luhn’s algorithm.


#include <stdio.h>
#include <cs50.h>
#include <math.h>


//Prototypes
int add_digits(int d);
int verify_num(int first);

int main(void)
{

    long long num = get_long_long("Number: ");
    long long copy_num = num;     //copy of unmodified user input for comparison of starting digits later on
    int odds = 0;     //sum of every first digit
    int evens = 0;    //sum of every second digit
    int tracker = 1;   //tracks position in number and length of number
    int current;    //holds current number

    while (num >= 1)
    {
        current = num % 10;

        //if num is a second digit
        if (tracker % 2 == 0)
        {
            evens += add_digits(current * 2);
        }
        else
        {
            odds += current;
        }
        tracker++;
        num = num / 10;
    }

    int sum = evens + odds;
    int first_digits = 0;     //the first two digits or first digit of the credit card number respectively
    int valid = 0;

    if (sum % 10 == 0)
    {
        switch (tracker - 1)
        {

            //for AMEX
            case (15):
                first_digits = copy_num / pow(10, 13);
                if (verify_num(first_digits))
                {
                    valid = 1;
                    printf("AMEX\n");
                }
                break;
            //for VISA
            case (13):
                first_digits = copy_num / pow(10, 12);
                if (verify_num(first_digits))
                {
                    valid = 1;
                    printf("VISA\n");
                }
                break;
            //For MASTERCARD || VISA
            case (16):
                first_digits = copy_num / pow(10, 15);
                if (first_digits == 4)
                {
                    valid = 1;
                    printf("VISA\n");
                }
                else
                {
                    first_digits = copy_num / pow(10, 14);
                    if (verify_num(first_digits))
                    {
                        valid = 1;
                        printf("MASTERCARD\n");
                    }
                    break;
                }

        }
    }

    if (!valid)
    {
        printf("INVALID\n");
    }


}

//add the digits of every second number multiplied by two together
int add_digits(int d)
{
    int total = 0;
    while (d >= 1)
    {
        total += d % 10;
        d = d / 10;
    }
    return total;
}

//verifies the number based on starting digits
int verify_num(int first)
{

    if (first == 51 || first == 52 || first == 53 || first == 54 || first == 55 || first == 4 || first == 34 || first == 37)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

