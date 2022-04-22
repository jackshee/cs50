#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average pixel value 
            float average_pixel_value = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = round(average_pixel_value);
        }
    }       

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width + 1) / 2; j++)
        {
            RGBTRIPLE tmp; 
            tmp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise variables to calculate average for each channel
            float sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Identify surrounding pixels
            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    // Check vertical boundaries
                    if (i + m < 0 || i + m > height -1)
                    {
                        continue;
                    }
                    // Check horizontal boundaries
                    if (j + n < 0 || j + n > width - 1)
                    {
                        continue;
                    }

                    sumRed += image[i + m][j + n].rgbtRed;
                    sumGreen += image[i + m][j + n].rgbtGreen;
                    sumBlue += image[i + m][j + n].rgbtBlue;
                    count++;
                }
                
            }
            
            tmp[i][j].rgbtRed = round(sumRed / count);
            tmp[i][j].rgbtGreen = round(sumGreen / count);
            tmp[i][j].rgbtBlue = round(sumBlue / count);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Convolve Gx and Gy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise matrix multiplcation sum
            double Gx_r = 0, Gx_g = 0, Gx_b = 0, Gy_r = 0, Gy_g = 0, Gy_b = 0;

            // Identify window to perform matrix multiplication 
            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + m < 0 || i + m > height - 1)
                    {
                        continue;
                    }
                    if (j + n < 0 || j + n > width - 1)
                    {
                        continue;
                    }

                    // Vertical edge detection
                    Gx_r += Gx[m + 1][n + 1] * image[i + m][j + n].rgbtRed;
                    Gx_g += Gx[m + 1][n + 1] * image[i + m][j + n].rgbtGreen;
                    Gx_b += Gx[m + 1][n + 1] * image[i + m][j + n].rgbtBlue;

                    // Horizontal edge detection
                    Gy_r += Gy[m + 1][n + 1] * image[i + m][j + n].rgbtRed;
                    Gy_g += Gy[m + 1][n + 1] * image[i + m][j + n].rgbtGreen;
                    Gy_b += Gy[m + 1][n + 1] * image[i + m][j + n].rgbtBlue;

                }
            }
            int blue = round(sqrt(Gx_b * Gx_b + Gy_b * Gy_b));
            int green = round(sqrt(Gx_g * Gx_g + Gy_g * Gy_g));
            int red = round(sqrt(Gx_r * Gx_r + Gy_r * Gy_r));

            tmp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            tmp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            tmp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }

    
    return;
}
