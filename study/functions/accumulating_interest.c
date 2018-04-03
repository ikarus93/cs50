//Implement a function with prototype
//double accumulate_interest(double balance, double rate);
//that takes two double s as input — a bank balance and an annual interest rate — and
//outputs an updated balance after 1 year of interest has accrued.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

double accumulate_interest(double balance, double rate);

int main(void)
{
    double start = get_double("Starting balance: ");
    double rate = get_double("Annual interest rate: ");
    double result = accumulate_interest(start, rate);
    printf("%.2f\n", result);

}

double accumulate_interest(double balance, double rate)
{
    return balance + (balance * rate);
}