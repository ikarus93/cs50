#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char letter = get_char("Please provide a lowercase letter: ");
    if (letter >= 'a' && letter <= 'z')
    {
        printf("%c\n", letter - ('a' - 'A'));
        return 0;
    }
    else
    {
        printf("Non lowercase letter\n");
        return 1;
    }
}