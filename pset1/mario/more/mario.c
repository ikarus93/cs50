#include <stdio.h>
#include <cs50.h>

void printTag(int i);
void printSpace(int size);

int main(void)
{
    int height = get_int("Height: ");

    while (height < 0 || height > 23)
    {
        height = get_int("Height: ");
    }

    for (int i = 0; i < height; i++)
    {
        printSpace(height - (i + 1));
        printTag(i);

        printSpace(2);
        printTag(i);
        printf("\n");

    }

}

void printTag(int i)
{
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
}

void printSpace(int size)
{
    for (int s = 0; s < size; s++)
    {
        printf(" ");
    }
}
