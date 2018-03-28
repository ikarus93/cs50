//Implement a program that encrypts messages using Vigenère’s cipher, per the below.


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Prototypes
int get_k(char c);
int modify_char(int c, int upper_bound, int lower_bound, int k);
int is_valid(string k);

int main(int argc, string argv[])
{

    //If commandline arguments are not sufficient
    if (argc != 2 || !is_valid(argv[1]))
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    string p = get_string("plaintext: ");
    printf("ciphertext: ");
    int key_length = strlen(argv[1]);     //length of key string to be able to wrap around it

    for (int i = 0, n = strlen(p), j = 0; i < n; i++, j++)
    {
        char current = p[i];
        int k = get_k(argv[1][j]);    //get the position in alphabet (0 indexed) for current index in key string
        if (isalpha(current))
        {
            //If the current char is uppercased
            if (current < 97)
            {
                current = modify_char(p[i], 90, 65, k);
            }
            else
            {
                current = modify_char(p[i], 122, 97, k);
            }
        } else {
            //reset j, in case non alphabetical character was encounted in plaintext
            j--;
        }
        printf("%c", current);


        //Wrap around key
        if (j + 1 == key_length)
        {
            j = -1;
        }
    }
    printf("\n");
    return 0;
}


//Gets the corresponding (A:0, B:1, C:2 etc) digit for each character of key
int get_k(char c)
{
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int digit = 0;
    for (int i = 0, n = strlen(alpha); i < n; i++)
    {
        if (toupper(c) == alpha[i])
        {
            digit = i;
        }
    }
    return digit;
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

//Checks the input key string for non alphabetical characters

int is_valid(string k)
{
    int valid = 1;

    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            valid = 0;
        }
    }

    return valid;
}