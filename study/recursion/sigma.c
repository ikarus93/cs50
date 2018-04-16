//Write a recursive function called sigma that adds the numbers 1 through n and returns the sum.


#include <stdio.h>
#include <cs50.h>

int sigma (int n);

int main(void)
{
    int n = get_int("Enter a positive integer: ");
    if (n <= 0)
    {
        printf("Integer entered not valid\n");
        return 1;
    }
    int result = 0;
    result += sigma(n);
    printf("Result: %d\n", result);
}

int sigma(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n + sigma(n - 1);
    }
}