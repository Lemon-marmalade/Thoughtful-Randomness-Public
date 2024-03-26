#include "bmp.h"
#include <math.h>

// added to help sepia
int fit_limit(int sepia);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over each pixelt
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //take average of hexadecimal value, and update pixel values to that average
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
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
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            fit_limit(sepiaRed);
            fit_limit(sepiaGreen);
            fit_limit(sepiaBlue);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])


int fit_limit(int sepia)
{
    if (sepia > 255)
    {
        sepia = 255;
    }
    return;
}
