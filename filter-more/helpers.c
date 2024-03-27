#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
     // loop over each pixelt
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // take average of hexadecimal value, and update pixel values to that average
            int average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // swap pixels
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
     // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            int sumRed, sumGreen, sumBlue;
            sumRed = sumGreen = sumBlue = 0;
            // for each pixel, sum up all the surrounding rgb values in 3 by 3 manner
            for (int a = (i - 1); a <= (i + 1); a++)
            {
                for (int b = (j - 1); b <= (j + 1); b++)
                {
                    // only add the values from copy if there is a pixel
                    if (a >= 0 && a <= (height - 1) && b >= 0 && b <= (width - 1))
                    {
                        sumRed += copy[a][b].rgbtRed;
                        sumGreen += copy[a][b].rgbtGreen;
                        sumBlue += copy[a][b].rgbtBlue;
                        // increment counter for instances pixels were actually added
                        counter++;
                    }
                }
            }
            image[i][j].rgbtRed = round((float) sumRed / (float) counter);
            image[i][j].rgbtGreen = round((float) sumGreen / (float) counter);
            image[i][j].rgbtBlue = round((float) sumBlue / (float) counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy for reference without manipulating final product
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}}
    int Gy[3][3] = {{-1,-2,-1},{-0,0,0},{1,2,1}}

    // loop over all pixels
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE grid[3][3] = {{copy[][],0,1},{-2,0,2},{-1,0,1}}
            int counter = 0;
            int sumRed, sumGreen, sumBlue;
            sumRed = sumGreen = sumBlue = 0;

            // loop for 3x3 grid
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    // if pixel exceeds boundaries, disregard pixels that are outside image
                    if ((i - 1 + x) > 0 && (i - 1 + x) <= (height - 1) && b >= 0 && b <= (width - 1))
                    {
                        copy[a][b].rbgtRed = copy[a][b].rbgtGreen = copy[a][b].rbgtBlue = 0;
                    }
                }
            }
            // multiply by Gx
            copy[i-1][j-1]rgbt.Red

        }
    }
    return;
}
