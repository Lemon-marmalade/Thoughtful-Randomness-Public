#include "helpers.h"
#include <math.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over each pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // compute sepia values, and update those values
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
