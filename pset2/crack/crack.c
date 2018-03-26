#define _XOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    //If commandline arguments are not sufficient
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    char salt[3] = {argv[1][0], argv[1][1], '\0'};    //creates the salt

    //Generate a base for iterations
    char base[6] = {'a','\0','\0','\0','\0','\0'};

   string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//Problem with comparison between hashed and base

    //Iterate over 26/52 * length of base possibilites
    for (int i = 0, a = 1, b = 0, c = 0, d = 0, e = 0; i < pow(52, 5) + 51; i++, a++)
    {
        base[0] = alpha[0 + a];
        if (strcmp(argv[1], crypt(base, salt)) == 0)
        {
            printf("%s\n", base);
            break;
        }

        if (a + 1 == strlen(alpha))
        {
            a = -1;
            base[1] = alpha[b];
            b++;
        }

        if (b  == strlen(alpha))
        {
            b = 0;
            base[2] = alpha[c];
            c++;
        }

        if (c == strlen(alpha))
        {
            c = 0;
            base[3] = alpha[d];
            d++;
        }

        if (d == strlen(alpha))
        {
            d = 0;
            base[4] = alpha[e];
            e++;
        }

       if (e == strlen(alpha))
        {
            e = 0;
        }
    }

}


