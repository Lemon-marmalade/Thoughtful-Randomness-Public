#include "bmp.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);
{
    //loop over each pixelt
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        //take average of hexadecimal value, and update pixel values to that average
        int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
        image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;

    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);
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

            int sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            int sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            int sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);
