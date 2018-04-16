//Implement your own version of the echo command. You’ll want to loop through the user’s arguments
//and print them out one-by-one, adding a space between them.


#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    printf("\n");
}