#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // TO DO
    float grayscale_av;

    // Scan through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average RGB values
            grayscale_av = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float) 3);
            image[i][j].rgbtRed = grayscale_av;
            image[i][j].rgbtGreen = grayscale_av;
            image[i][j].rgbtBlue = grayscale_av;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // TO DO
    float sepiaRed, sepiaGreen, sepiaBlue;

    // Scan through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get new RGB values with formulae
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            // If value exceeds 255, it sets to 255
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
    // TO DO
    int tmpRed, tmpGreen, tmpBlue;

    // Scan through pixels
    for (int i = 0; i < height; i++)
    {
        // Only scan through half of the image's columns
        for (int j = 0; j <= round((width - 1) / 2); j++)
        {
            // Store RBG values from current pixel into temporary variables
            tmpRed = image[i][j].rgbtRed;
            tmpGreen = image[i][j].rgbtGreen;
            tmpBlue = image[i][j].rgbtBlue;
            // Store RBG value of pixel on opposite side of row into current pixel
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            // Store temporary variables into pixels on opposite side of row
            image[i][width - 1 - j].rgbtRed = tmpRed;
            image[i][width - 1 - j].rgbtGreen = tmpGreen;
            image[i][width - 1 - j].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // TO DO
    int Red, Green, Blue;
    int pixels;
    float averageRed, averageGreen, averageBlue;

    // Declare a new variable of RGBTRIPLE struct
    RGBTRIPLE original[height][width];
    // Scan through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    // Scan through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Total values of center pixels
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                Red = original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i][j - 1].rgbtRed +
                      original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed +
                      original[i + 1][j + 1].rgbtRed;
                Green = original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i][j -
                        1].rgbtGreen +
                        original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen +
                        original[i + 1][j + 1].rgbtGreen;
                Blue = original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i][j - 1].rgbtBlue
                       +
                       original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue +
                       original[i + 1][j + 1].rgbtBlue;
                pixels = 9;
            }
            // Total values of first row excluding corners
            else if (i == 0 && j > 0 && j < width - 1)
            {
                Red = original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed +
                      original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed;
                Green = original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen +
                        original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen;
                Blue = original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue +
                       original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue;
                pixels = 6;

            }
            // Total values oflast row excluding corners
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                Red = original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i][j - 1].rgbtRed +
                      original[i][j].rgbtRed + original[i][j + 1].rgbtRed;
                Green = original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i][j -
                        1].rgbtGreen +
                        original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen;
                Blue =  original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i][j -
                        1].rgbtBlue +
                        original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue;
                pixels = 6;
            }
            // Total values of first column excluding corners
            else if (i > 0 && i < height - 1 && j == 0)
            {
                Red = original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed +
                      original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed;
                Green = original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen +
                        original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen;
                Blue = original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue +
                       original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue;
                pixels = 6;
            }
            // Total values of last column excluding corners
            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                Red = original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j].rgbtRed +
                      original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed;
                Green = original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen +
                        original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen;
                Blue = original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue +
                       original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue;
                pixels = 6;
            }
            // Total values of top left pixel
            else if (i == 0  && j == 0)
            {
                Red = original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed;
                Green = original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen;
                Blue = original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue;
                pixels = 4;
            }
            // Total values of top right pixel
            else if (i == 0  && j == width - 1)
            {
                Red = original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed;
                Green = original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen;
                Blue = original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue;
                pixels = 4;
            }
            // Total values of  bottom left pixel
            else if (i == height - 1  && j == 0)
            {
                Red = original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed;
                Green = original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen;
                Blue = original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue;
                pixels = 4;
            }
            // Total values of bottom right pixel
            else if (i == height - 1  && j == width - 1)
            {
                Red = original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j].rgbtRed;
                Green = original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen;
                Blue = original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue;
                pixels = 4;
            }
            // Calculate the average of total values
            averageRed = round(Red / (float) pixels);
            averageGreen = round(Green / (float) pixels);
            averageBlue = round(Blue / (float) pixels);
            // If value exceeds 255, it sets to 255
            if (averageRed > 255)
            {
                averageRed = 255;
            }
            if (averageGreen > 255)
            {
                averageGreen = 255;
            }
            if (averageBlue > 255)
            {
                averageBlue = 255;
            }
            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;
        }
    }
    return;
}
