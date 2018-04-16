//Write a program that prints out the total number of characters in the command line arguments given to the program.
//Ignore whitespace (for example, spaces, newlines, and tab characters),and ignore the program name.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int total = 0;
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++, total++);
    }

    printf("%d\n", total);
}