#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = get_int("Height: ");

    while (height < 0 || height > 23)
    {
        height = get_int("Height: ");
    }


    for (int i = 0; i < height; i++)
    {
        for (int w = 0; w < height - (i + 1); w++)
            //Prints whitespace
        {
            printf(" ");
        }

        for (int j = 0; j <= i + 1; j++)
            //Prints the actual pyramid, index J gets an additional iteration to start with printing two hashtags
        {
            printf("#");
        }

        printf("\n");    //print newline after each iteration
    }
}

