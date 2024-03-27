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
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
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
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{-0,0,0},{1,2,1}};

    // loop over all pixels
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // copy for reference without manipulating final product


            int GxRed, GxGreen, GxBlue,GyRed, GyGreen, GyBlue;
            GxRed = GxGreen = GxBlue = GyRed = GyGreen = GyBlue = 0;

            // loop for 3x3 grid (modified to more easily link array of kernels)
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0 - 1; b < 3; b++)
                {
                    // if pixel exceeds boundaries, disregard pixels that are outside image
                    if ((i - 1 + a) > 0 && (i - 1 + a) && (height - 1) && (j - 1 + a) >= 0 && (j - 1 + a) <= (width - 1))
                    {
                        GxRed = GxRed + copy[a][b].rgbtRed * Gx[a][b];
                        GxGreen = GxGreen + copy[a][b].rgbtGreen * Gx[a][b];
                        GxBlue = GxBlue + copy[a][b].rgbtBlue * Gx[a][b];

                        GyRed = GyRed + copy[a][b].rgbtRed * Gy[a][b];
                        GyGreen = GyGreen + copy[a][b].rgbtGreen * Gy[a][b];
                        GyBlue = GyBlue + copy[a][b].rgbtBlue * Gy[a][b];
                    }
                    else
                    {
                        continue;
                    }
                }
                // calculate square root of Gx^2+Gy^2
                int SobelRed = round(sqrt(pow(GxRed,2)+pow(GyRed,2)));
                int SobelGreen = round(sqrt(pow(GxGreen,2)+pow(GyGreen,2)));
                int SobelBlue = round(sqrt(pow(GxBlue,2)+pow(GyBlue,2)));

                // deal with values exceeding 255
                if(SobelRed > 255)
                {
                    SobelRed = 255;
                }
                if(SobelGreen > 255)
                {
                    SobelGreen = 255;
                }
                if(SobelBlue > 255)
                {
                    SobelBlue = 255;
                }
                //transer values
                image[i][j].rgbtRed = SobelRed;
                image[i][j].rgbtGreen = SobelGreen;
                image[i][j].rgbtBlue = SobelBlue;
            }
        }
    }
    return;
}
