# Questions

## What's `stdint.h`?
stdint.h contains integers of a fixed width (numbers of bits used for storage), such as 'uint8_t', 'uint32_t', 'int32_t' and 'uint16_t'.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

They let us store integers of a fixed size. That way we can easily iterate through file headers, knowing the size of each part of the header.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE - 1 BYTE /8 bits
DWORD - 4 BYTES / 32 bits
LONG - 4 BYTES / 32 bits
WORD - 2 BYTES / 16 bits

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM (ASCII)
0x42 0x4D (hexadecimal)
66 77  (decimal)
## What's the difference between `bfSize` and `biSize`?

bfSize marks the size in bytes of the entire bitmap file.
biSize marks the size of the bitmap infoheader structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative, it means that top-down DIB that originates in the top-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The biBitCount specifies the color depth/bits per pixel of the DIB.
It must be either:
0 - Specified by the jpeg/png format
1 - monochrome
4 - a maximum of 16 colors
8 - a maximum of 256 colors
16 - 2 ^ 16 colors
24 - 2 ^ 24 colors
32 - 2 ^ 32 colors

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the input file doesnt exist or the path is wrong,
If the output file cant be created for some reason.

## Why is the third argument to `fread` always `1` in our code?

Because we want to read one element of the predefined size at a time.
e.g.     fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
Reads one element of the size of BITMAPFILEHEADER at a time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

The padding is 0, as the formula breaks down to:
4 - ((3 * 12) % 4) % 4
4 - (0) % 4
4 % 4
= 0

## What does `fseek` do?

fseek skips over a certain amount of bytes in the scanline / sets the file position to a given offset.

## What is `SEEK_CUR`?

SEEK_CUR holds the current position in the file.
In the current example it means that the offset is adden from the current position in the file.
