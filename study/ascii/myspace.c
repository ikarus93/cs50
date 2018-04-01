#include <stdio.h>
#include <cs50.h>
#include <string.h>

int is_upper(char c);
int is_alpha(char c);
char to_upper(char c);
char to_lower(char c);


int main(void)
{
    char *str = get_string("Please provide a valid string ");
    char copy[strlen(str) + 1];

    if (!is_alpha(str[0]))
    {
        copy[0] = str[0];
    }
    else
    {
        copy[0] = to_upper(str[0]);
    }


    for (int i = 1, n = strlen(str); i < n; i++)
    {
        if (is_alpha(str[i]))
        {
            if (i % 2 != 0)
            {
                copy[i] = to_lower(str[i]);
            }
            else
            {
                copy[i] = to_upper(str[i]);
            }
        }
        else
        {
            copy[i] = str[i];
        }

    }

    printf("%s\n", copy);
}

int is_upper(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char to_upper(char c)
{
    if (!is_upper(c))
    {
        return c - ('a' - 'A');
    }
    else
    {
        return c;
    }

}

char to_lower(char c)
{
    if (is_upper(c))
    {
        return c + ('a' - 'A');
    }
    else
    {
        return c;
    }

}

int is_alpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return 1;
    }
    else
    {
        return 0;
}

}