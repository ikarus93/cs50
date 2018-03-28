//Implement a program that encrypts messages using Caesar’s cipher, per the below.

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


//Prototypes
int modify_char(int c, int upper_bound, int lower_bound, int k);

int main(int argc, string argv[])
{
    //If not only 1 command line argument is supplied, terminate early
    if (argc != 2)
    {
        printf("Usage: ./caesar k");
        return 1;
    }

    int k = atoi(argv[1]) % 26;      //in case k is larger than alphabet
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0,  n = strlen(plain); i < n; i++)
    {
        char current = plain[i];
        if (isalpha(current))
        {
            //If the current char is uppercased
            if (current < 97)
            {
                current = modify_char(plain[i], 90, 65, k);
            }
            else
            {
                current = modify_char(plain[i], 122, 97, k);
            }
        }
        printf("%c", current);
    }
    printf("\n");
    return 0;
}

//Modifies the character based on it being upper/lower case, using upper/lower bound to differentiate
int modify_char(int c, int upper_bound, int lower_bound, int k)
{
    int current = (c + k) % upper_bound;
    //If character is smaller than lower bound add it to A/a - 1
    if (current < lower_bound)
    {
        current = (lower_bound - 1) + current;
    }
    return current;
}