#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{

    // Creating variables for file names
    char *infile = argv[2];
    char *outfile = argv[3];

    // Validating there are 4 arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // Validating n is a positive integer that is less than or equal to 100.
    int n = atoi(argv[1]);
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "n must be greater than 0 and less than or equal to 100\n");
        return 1;
    }

    // Opening input file
    FILE *inptr = fopen(infile, "r");

    // Checking if there is a readable file. If not, then end program.
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Opening output file
    FILE *outptr = fopen(outfile, "w");

    // Checking if the file is writeable. If not, then end program.
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Declaring variables for infile header files
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;

    // Declaring variables for outfile header files
    BITMAPFILEHEADER newBf;
    BITMAPINFOHEADER newBi;

    // read infile's BITMAPFILEHEADER & BITMAPINFOHEADER files
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Validating infile is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Initialize outfile's header files with the value of the infile's
    newBf = bf;
    newBi = bi;

    // resize outfile's info header height and width values by n
    newBi.biWidth = bi.biWidth * n;
    newBi.biHeight = bi.biHeight * n;

    // Declare infile and outfile padding so we can handle outfile image size
    int originalPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (newBi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Modify biSizeImage in outfile's info header
    newBi.biSizeImage = (newBi.biWidth * sizeof(RGBTRIPLE) + newPadding) * abs(newBi.biHeight);

    // Modify bfSize in outfile's file header
    newBf.bfSize = newBi.biSizeImage + newBf.bfOffBits;

    // Write new BITMAPFILEHEADER & BITMAPTINFOHEADER values for outfile
    fwrite(&newBf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&newBi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write resized data to the outfile
    // Loop through infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // VERTICAL resizing: write each line n times
        for (int v = 0; v < n; v++)
        {
            // iterate over pixels in infile's scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // HORIZONTAL resizing:  write RGB triple to outfile
                for (int h = 0; h < n; h++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over infile padding, if any
            fseek(inptr, originalPadding, SEEK_CUR);

            // add any necessary padding to outfile
            for (int p = 0; p < newPadding; p++)
            {
                fputc(0x00, outptr);
            }

            // move pointer back to begining of the scan line (we need to rewrite the line)
            // We have to use sizeof(RGBTRIPLE) because width is in pixels not bytes.
            // fseek moves the pointer to a "byte" location and we are reading triples which are pixels.
            // 1 pixel = sizeof(RGBTRIPLE) which is 3 types...while... 1 padding = 1 byte
            fseek(inptr, -((bi.biWidth * sizeof(RGBTRIPLE)) + originalPadding), SEEK_CUR);
        }

        // move pointer ahead to the end of the last scanline to we pickup the next scanline
        fseek(inptr, (bi.biWidth * sizeof(RGBTRIPLE)) + originalPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
