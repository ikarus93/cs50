//Reveals who killed Mr.Boddy

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Invalid input file\n");
        return 2;
    }

    FILE *outptr = fopen(outfile, "w");

    if (outptr == NULL)
    {
        fprintf(stderr, "Invalid output file\n");
        return 3;
    }

    //Read bitmap fileheader
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(bf), 1, inptr);

    //Read bitmap infoheader
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(bi), 1, inptr);

    // check if infile is a 24-bit uncompressed BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

        // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //if pixels are completely red, turn them white
            if (triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00 && triple.rgbtRed == 0xff)
            {
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtRed = 0xff;
            }
            //if pixels arent completely red or completely white, turn them black
            else if (triple.rgbtBlue != 0xff || triple.rgbtGreen != 0xff || triple.rgbtRed != 0xff)
            {
                triple.rgbtBlue = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtRed = 0x00;
            }
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

        // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}