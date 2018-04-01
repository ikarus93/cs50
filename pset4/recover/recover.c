//Implement a program called recover that recovers JPEGs from a forensic image.


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int is_jpeg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //if not only 1 argument is given
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: recover memorycard\n");
        return 1;
    }

    //open file
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        fprintf(stderr, "Invalid forensic image\n");
        return 2;
    }


    //create buffer of type BYTE array to hold each 512 bytes
    BYTE buffer[512];
    //variable to track how many files have been created, and create dynamic filenames with it
    int filenum = 0;

    //iterate over buffers until first jpg is found
    while (!feof(card))
    {
        fread(buffer, 512, 1, card);


        if (is_jpeg(buffer))
        {
            //retrieve all files
            while(!feof(card))
            {
                //holds the filename
                char *filename = malloc(8 * sizeof(char) + 1);
                //create dynamic filename
                sprintf(filename, "%03i.jpg", filenum);

                //open outfile
                FILE *jpg = fopen(filename, "w");
                fwrite(buffer, 512, 1, jpg);
                fread(buffer, 512, 1, card);
                //
                while(!is_jpeg(buffer))
                {
                    if(feof(card))
                    {   //
                        break;
                    }
                    fwrite(buffer, 512, 1, jpg);
                    fread(buffer, 512, 1, card);


                }
                //close jpg
                fclose(jpg);
                //increment filecounter
                filenum++;
                //free memory allocated at the heap
                free(filename);
            }
        }
    }
    fclose(card);
}

int is_jpeg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

