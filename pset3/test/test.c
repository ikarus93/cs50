#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_semitones(int final_octave, string keys, int direction, int i);
int frequency(string note);

int main(void)
{
    string s = get_string("");
    frequency(s);
}




int frequency(string note)
{
    // TODO
    char key = note[0];
    char octave;
    char accidental = 0;

    //Check if input string "note" contains an accidental
    if (note[2] == '\0')
    {
        octave = note[1];
    }
    else
    {
        accidental = note[1];
        octave = note[2];
    }
    //Iterate over C-B counting the semitones, simulating one octave from piano keyboard
    string keys = "CDEFGAB";
    octave = octave - '0';

    int semitones = 0;


    int i = 0;
    //Get index of key in string keys
    for (int j = 0; keys[j] != '\0'; j++)
    {
        if (keys[j] == key)
        {
            i = j;
        }
    }

    int final_octave = octave;

    //Covering edgecase
    if(octave == 4 && key == 'B')
    {
        semitones += 2;
    }
    //second annoying edge case
    else if (octave == 4 && ((key == 'B' && accidental == 'b') || (key == 'A' && accidental == '#' )))
    {
        semitones++;
    }
    else
    {
        int direction = 1;
        if (octave > 4)
        {
            direction = 0;
        }

        semitones = get_semitones(final_octave, keys, direction, i);

    }   //end of else

    //adjusting semitones according to accidental
    if (octave != 4)
    {
        if (accidental == '#')
        {
            semitones++;
        }
        else if (accidental == 'b')
        {
            semitones--;
        }
    }

    float result = (pow(2, semitones/12.0) * 440.00);
    return round(result);

}

int get_semitones(int final_octave, string keys, int direction, int i)
{
    int semitones = 0;
    while (keys[i] != 'A' || final_octave != 4)
    {
        if (direction)
        {
            if (keys[i] == 'E' || keys[i] == 'B')
            {
                semitones--;
            }
            else
            {
                semitones -= 2;
            }

            if (keys[i] == 'B')
            {
                i = 0;
                final_octave ++;
            }
            else
            {
                i++;
            }
        }
        else
        {
            if (keys[i] == 'F' || keys[i] == 'C')
            {
                semitones ++;
            }
            else
            {
                semitones += 2;
            }

            if (keys[i] == 'C')
            {
                i = 6;
                final_octave --;
            }
            else
            {
                i--;
            }
        }

    }
    return semitones;
}