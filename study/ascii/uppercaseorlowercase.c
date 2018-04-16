//Complete the following program that prompts the user to enter an alphabetical character
//and determines whether the character is uppercase or lowercase.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char letter = get_char("Letter: ");
    if (letter >= 'A' && letter <= 'Z')
    {
        printf("Thanks for the uppercase letter");
    }
    else if (letter >= 'a' && letter <= 'z')
    {
        printf("Thanks for the lowercase letter");
    }
    else
    {
        printf("Non alphabetical character");
    }
    printf("\n");
    return 0;
}