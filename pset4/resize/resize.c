#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char * argv[])
{

    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize integer infile outfile\n");
        return 1;
    }
    //typecast integer n
    int n = atoi(argv[1]);

    if (n > 100 || n <= 0)
    {
        fprintf(stderr, "N should be a positive integer no larger than 100\n");
        return 1;
    }

        // get filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    //retrieve the infiles padding if any
    int oldPadding = (4 - ((bi.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;

    //securing old bitmap width and height for input file iteration
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    //Update header width and height
    bi.biWidth *= n;
    bi.biHeight *= n;

    //set padding
    int newPadding = (4 - ((bi.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;

    //update infoheader total image size
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);

    //set fileheader total size
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //write output files fileheaders
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    //iterate over infiles scanlines
    for (int i = 0, height = abs(oldHeight); i < height; i++)
    {
        //resize vertically
        for (int x = 0; x < n; x++)
        {
            //Iterate over infiles pixels
            for (int j = 0; j < oldWidth; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //Print pixels to outputfile
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

                //Write padding to outfile
                for (int l = 0; l < newPadding; l++)
                {
                    fputc(0x00, outptr);
                }

                //set cursor back
                fseek(inptr, -(sizeof(RGBTRIPLE) * oldWidth), SEEK_CUR);

        }


        //Skip over one row of infile
        fseek(inptr, sizeof(RGBTRIPLE) * oldWidth, SEEK_CUR);
        //Skip over infiles padding
        fseek(inptr, oldPadding, SEEK_CUR);
    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}