//Implement a program that prints out a double half-pyramid of a specified height, per the below.


#include <stdio.h>
#include <cs50.h>

//Prototypes
void printTag(int i);
void printSpace(int size);

int main(void)
{
    int height;    //Container for User selection
    do
    {
        height = get_int("Height: ");
    }
    while (height < 0 || height > 23);

    for (int i = 0; i < height; i++)
    {
        printSpace(height - (i + 1));
        printTag(i);

        printSpace(2);
        printTag(i);
        printf("\n");

    }

}

//Prints each Symbol
void printTag(int i)
{
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
}


//Prints each space
void printSpace(int size)
{
    for (int s = 0; s < size; s++)
    {
        printf(" ");
    }
}
