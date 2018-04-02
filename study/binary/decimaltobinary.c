//Write a program that takes a positive decimal value as input and prints out that number in binary notation.


#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    int decimal = get_int("Please enter a positive decimal value ");
    if (decimal < 0)
    {
        printf("The integer entered is not positive\n");
        return 1;
    }

    //Initial memory allocation
    char *binary = malloc(sizeof(char) + 1);
    int length = 1;
    *binary = (decimal % 2) + '0';
    decimal = decimal / 2;

    while (decimal > 0)
    {
        length++;
        binary = realloc(binary, sizeof(char) + length);
        char *temp = malloc(sizeof(char) + 1);
        *temp = (decimal % 2) + '0';
        decimal = decimal / 2;
        strcat(binary, temp);
        free(temp);

    }
    //Reverse the binary string
    char reversed[strlen(binary) + 1];
    for (int j = strlen(binary), i = 0; i < strlen(binary); i++, j--)
    {
        reversed[j] = binary[i];
    }
    printf("%s\n", reversed);
    free(binary);
}