#include "helpers.h"
#include <math.h>


//Multiplying Matrices (for edges)
void Mult(RGBTRIPLE a[3][3], int b[3][3], int *zRed, int *zGreen, int *zBlue);

//Regulating pixels above 255
void regulate(int *pixel);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // considering each pixel
            float avg = 0;
            avg += image[i][j].rgbtRed;
            avg += image[i][j].rgbtGreen;
            avg += image[i][j].rgbtBlue;
            avg /= 3;
            int res = round(avg);

            image[i][j].rgbtRed = res;
            image[i][j].rgbtGreen = res;
            image[i][j].rgbtBlue = res;

        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE newimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // considering each pixel
            newimage[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            newimage[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            newimage[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // considering each pixel
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue;

        }

    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newimage[height][width];


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width); j++)
        {

            // considering each pixel in the original image
            int sumred, sumgreen, sumblue;
            int boxes;


            if (i == 0 && j == 0) // very first corner --> boxes = 4
            {
                boxes = 4;

                sumred = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

            }
            else if (i == height - 1 && j == 0) // very down corner
            {
                boxes = 4;

                sumred = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
            }
            else if (i == 0 && j == width - 1) // very upper-right corner
            {
                boxes = 4;

                sumred = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
            }
            else if (i == height - 1 && j == width - 1) // very lower-right corner
            {
                boxes = 4;
                sumred = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue;
            }
            ///// now we must deal with edges which has 6 boxes
            else if (j == 0) //left edge
            {
                boxes = 6;

                sumred = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                         image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                           image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                          image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;

            }
            else if (j == width - 1) // right edge
            {
                boxes = 6;

                sumred = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                         image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                           image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                          image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue;

            }
            else if (i == 0) //upper edge
            {
                boxes = 6;

                sumred = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                         image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                           image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                          image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            }
            else if (i == height - 1)
            {
                boxes = 6;

                sumred = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                         image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                           image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                          image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;


            }

            else // no edges or corners
            {
                boxes = 9;

                sumred = image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                         image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                         image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;

                sumgreen = image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                           image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                           image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;

                sumblue = image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                          image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                          image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;

            }

            float avgred = (float)sumred / (float)boxes;
            float avggreen = (float)sumgreen / (float)boxes;
            float avgblue = (float)sumblue / (float)boxes;


            newimage[i][j].rgbtRed = round(avgred);
            newimage[i][j].rgbtGreen = round(avggreen);
            newimage[i][j].rgbtBlue = round(avgblue);

        }

    }

    //copying the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue;
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int Gx[3][3] = {{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}

    };

    int Gy[3][3] = {{-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}

    };

    RGBTRIPLE newimage[height][width];
    RGBTRIPLE tmp[3][3];
    int xRed, xGreen, xBlue, yRed, yGreen, yBlue; //Gx & Gy Variables

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width); j++)
        {

            // considering each pixel in the original image

            if (i == 0 && j == 0) // very first corner
            {
                tmp[0][1].rgbtRed = tmp[0][1].rgbtGreen = tmp[0][1].rgbtBlue = 0;
                tmp[0][0].rgbtRed = tmp[0][0].rgbtGreen = tmp[0][0].rgbtBlue = 0;
                tmp[0][2].rgbtRed = tmp[0][2].rgbtGreen = tmp[0][2].rgbtBlue = 0;
                tmp[1][0].rgbtRed = tmp[1][0].rgbtGreen = tmp[1][0].rgbtBlue = 0;
                tmp[2][0].rgbtRed = tmp[2][0].rgbtGreen = tmp[2][0].rgbtBlue = 0;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[1][2].rgbtRed = image[i][j + 1].rgbtRed;
                tmp[1][2].rgbtGreen = image[i][j + 1].rgbtGreen;
                tmp[1][2].rgbtBlue = image[i][j + 1].rgbtBlue;

                tmp[2][1].rgbtRed = image[i + 1][j].rgbtRed;
                tmp[2][1].rgbtGreen = image[i + 1][j].rgbtGreen;
                tmp[2][1].rgbtBlue = image[i + 1][j].rgbtBlue;

                tmp[2][2].rgbtRed = image[i + 1][j + 1].rgbtRed;
                tmp[2][2].rgbtGreen = image[i + 1][j + 1].rgbtGreen;
                tmp[2][2].rgbtBlue = image[i + 1][j + 1].rgbtBlue;

                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;

            }
            else if (i == height - 1 && j == 0) // very down corner
            {
                tmp[0][0].rgbtRed = tmp[0][0].rgbtGreen = tmp[0][0].rgbtBlue = 0;
                tmp[1][0].rgbtRed = tmp[1][0].rgbtGreen = tmp[1][0].rgbtBlue = 0;
                tmp[2][0].rgbtRed = tmp[2][0].rgbtGreen = tmp[2][0].rgbtBlue = 0;
                tmp[2][1].rgbtRed = tmp[2][1].rgbtGreen = tmp[2][1].rgbtBlue = 0;
                tmp[2][2].rgbtRed = tmp[2][2].rgbtGreen = tmp[2][2].rgbtBlue = 0;

                tmp[0][1].rgbtRed = image[i - 1][j].rgbtRed;
                tmp[0][1].rgbtGreen = image[i - 1][j].rgbtGreen;
                tmp[0][1].rgbtBlue = image[i - 1][j].rgbtBlue;

                tmp[0][2].rgbtRed = image[i - 1][j + 1].rgbtRed;
                tmp[0][2].rgbtGreen = image[i - 1][j + 1].rgbtGreen;
                tmp[0][2].rgbtBlue = image[i - 1][j + 1].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[1][2].rgbtRed = image[i][j + 1].rgbtRed;
                tmp[1][2].rgbtGreen = image[i][j + 1].rgbtGreen;
                tmp[1][2].rgbtBlue = image[i][j + 1].rgbtBlue;

                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;


            }
            else if (i == 0 && j == width - 1) // very upper-right corner
            {
                tmp[0][0].rgbtRed = tmp[0][0].rgbtGreen = tmp[0][0].rgbtBlue = 0;
                tmp[0][1].rgbtRed = tmp[0][1].rgbtGreen = tmp[0][1].rgbtBlue = 0;
                tmp[0][2].rgbtRed = tmp[0][2].rgbtGreen = tmp[0][2].rgbtBlue = 0;
                tmp[1][2].rgbtRed = tmp[1][2].rgbtGreen = tmp[1][2].rgbtBlue = 0;
                tmp[2][2].rgbtRed = tmp[2][2].rgbtGreen = tmp[2][2].rgbtBlue = 0;

                tmp[1][0].rgbtRed = image[i][j - 1].rgbtRed;
                tmp[1][0].rgbtGreen = image[i][j - 1].rgbtGreen;
                tmp[1][0].rgbtBlue = image[i][j - 1].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[2][0].rgbtRed = image[i + 1][j - 1].rgbtRed;
                tmp[2][0].rgbtGreen = image[i + 1][j - 1].rgbtGreen;
                tmp[2][0].rgbtBlue = image[i + 1][j - 1].rgbtBlue;

                tmp[2][1].rgbtRed = image[i + 1][j].rgbtRed;
                tmp[2][1].rgbtGreen = image[i + 1][j].rgbtGreen;
                tmp[2][1].rgbtBlue = image[i + 1][j].rgbtBlue;

                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;



            }
            else if (i == height - 1 && j == width - 1) // very lower-right corner
            {
                tmp[0][2].rgbtRed = tmp[0][2].rgbtGreen = tmp[0][2].rgbtBlue = 0;
                tmp[1][2].rgbtRed = tmp[1][2].rgbtGreen = tmp[1][2].rgbtBlue = 0;
                tmp[2][0].rgbtRed = tmp[2][0].rgbtGreen = tmp[2][0].rgbtBlue = 0;
                tmp[2][1].rgbtRed = tmp[2][1].rgbtGreen = tmp[2][1].rgbtBlue = 0;
                tmp[2][2].rgbtRed = tmp[2][2].rgbtGreen = tmp[2][2].rgbtBlue = 0;

                tmp[0][0].rgbtRed = image[i - 1][j - 1].rgbtRed;
                tmp[0][0].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                tmp[0][0].rgbtBlue = image[i - 1][j - 1].rgbtBlue;

                tmp[0][1].rgbtRed = image[i - 1][j].rgbtRed;
                tmp[0][1].rgbtGreen = image[i - 1][j].rgbtGreen;
                tmp[0][1].rgbtBlue = image[i - 1][j].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[1][0].rgbtRed = image[i][j - 1].rgbtRed;
                tmp[1][0].rgbtGreen = image[i][j - 1].rgbtGreen;
                tmp[1][0].rgbtBlue = image[i][j - 1].rgbtBlue;

                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;


            }
            ///// now we must deal with edges which has 6 boxes
            else if (j == 0) //left edge
            {

                tmp[0][0].rgbtRed = tmp[0][0].rgbtGreen = tmp[0][0].rgbtBlue = 0;
                tmp[1][0].rgbtRed = tmp[1][0].rgbtGreen = tmp[1][0].rgbtBlue = 0;
                tmp[2][0].rgbtRed = tmp[2][0].rgbtGreen = tmp[2][0].rgbtBlue = 0;

                tmp[0][1].rgbtRed = image[i - 1][j].rgbtRed;
                tmp[0][1].rgbtGreen = image[i - 1][j].rgbtGreen;
                tmp[0][1].rgbtBlue = image[i - 1][j].rgbtBlue;

                tmp[0][2].rgbtRed = image[i - 1][j + 1].rgbtRed;
                tmp[0][2].rgbtGreen = image[i - 1][j + 1].rgbtGreen;
                tmp[0][2].rgbtBlue = image[i - 1][j + 1].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[1][2].rgbtRed = image[i][j + 1].rgbtRed;
                tmp[1][2].rgbtGreen = image[i][j + 1].rgbtGreen;
                tmp[1][2].rgbtBlue = image[i][j + 1].rgbtBlue;

                tmp[2][1].rgbtRed = image[i + 1][j].rgbtRed;
                tmp[2][1].rgbtGreen = image[i + 1][j].rgbtGreen;
                tmp[2][1].rgbtBlue = image[i + 1][j].rgbtBlue;

                tmp[2][2].rgbtRed = image[i + 1][j + 1].rgbtRed;
                tmp[2][2].rgbtGreen = image[i + 1][j + 1].rgbtGreen;
                tmp[2][2].rgbtBlue = image[i + 1][j + 1].rgbtBlue;

                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;



            }
            else if (j == width - 1) // right edge
            {
                tmp[0][2].rgbtRed = tmp[0][2].rgbtGreen = tmp[0][2].rgbtBlue = 0;
                tmp[1][2].rgbtRed = tmp[1][2].rgbtGreen = tmp[1][2].rgbtBlue = 0;
                tmp[2][2].rgbtRed = tmp[2][2].rgbtGreen = tmp[2][2].rgbtBlue = 0;

                tmp[0][0].rgbtRed = image[i - 1][j - 1].rgbtRed;
                tmp[0][0].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                tmp[0][0].rgbtBlue = image[i - 1][j - 1].rgbtBlue;

                tmp[0][1].rgbtRed = image[i - 1][j].rgbtRed;
                tmp[0][1].rgbtGreen = image[i - 1][j].rgbtGreen;
                tmp[0][1].rgbtBlue = image[i - 1][j].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[1][0].rgbtRed = image[i][j - 1].rgbtRed;
                tmp[1][0].rgbtGreen = image[i][j - 1].rgbtGreen;
                tmp[1][0].rgbtBlue = image[i][j - 1].rgbtBlue;

                tmp[2][0].rgbtRed = image[i + 1][j - 1].rgbtRed;
                tmp[2][0].rgbtGreen = image[i + 1][j - 1].rgbtGreen;
                tmp[2][0].rgbtBlue = image[i + 1][j - 1].rgbtBlue;

                tmp[2][1].rgbtRed = image[i + 1][j].rgbtRed;
                tmp[2][1].rgbtGreen = image[i + 1][j].rgbtGreen;
                tmp[2][1].rgbtBlue = image[i + 1][j].rgbtBlue;

                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;



            }
            else if (i == 0) //upper edge
            {
                tmp[0][0].rgbtRed = tmp[0][0].rgbtGreen = tmp[0][0].rgbtBlue = 0;
                tmp[0][1].rgbtRed = tmp[0][1].rgbtGreen = tmp[0][1].rgbtBlue = 0;
                tmp[0][2].rgbtRed = tmp[0][2].rgbtGreen = tmp[0][2].rgbtBlue = 0;

                tmp[1][0].rgbtRed = image[i][j - 1].rgbtRed;
                tmp[1][0].rgbtGreen = image[i][j - 1].rgbtGreen;
                tmp[1][0].rgbtBlue = image[i][j - 1].rgbtBlue;

                tmp[1][2].rgbtRed = image[i][j + 1].rgbtRed;
                tmp[1][2].rgbtGreen = image[i][j + 1].rgbtGreen;
                tmp[1][2].rgbtBlue = image[i][j + 1].rgbtBlue;

                tmp[1][0].rgbtRed = image[i][j - 1].rgbtRed;
                tmp[1][0].rgbtGreen = image[i][j - 1].rgbtGreen;
                tmp[1][0].rgbtBlue = image[i][j - 1].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[2][0].rgbtRed = image[i + 1][j - 1].rgbtRed;
                tmp[2][0].rgbtGreen = image[i + 1][j - 1].rgbtGreen;
                tmp[2][0].rgbtBlue = image[i + 1][j - 1].rgbtBlue;

                tmp[2][1].rgbtRed = image[i + 1][j].rgbtRed;
                tmp[2][1].rgbtGreen = image[i + 1][j].rgbtGreen;
                tmp[2][1].rgbtBlue = image[i + 1][j].rgbtBlue;

                tmp[2][2].rgbtRed = image[i + 1][j + 1].rgbtRed;
                tmp[2][2].rgbtGreen = image[i + 1][j + 1].rgbtGreen;
                tmp[2][2].rgbtBlue = image[i + 1][j + 1].rgbtBlue;


                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;



            }
            else if (i == height - 1) // lower edge
            {

                tmp[2][0].rgbtRed = tmp[2][0].rgbtGreen = tmp[2][0].rgbtBlue = 0;
                tmp[2][1].rgbtRed = tmp[2][1].rgbtGreen = tmp[2][1].rgbtBlue = 0;
                tmp[2][2].rgbtRed = tmp[2][2].rgbtGreen = tmp[2][2].rgbtBlue = 0;

                tmp[0][0].rgbtRed = image[i - 1][j - 1].rgbtRed;
                tmp[0][0].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                tmp[0][0].rgbtBlue = image[i - 1][j - 1].rgbtBlue;

                tmp[0][1].rgbtRed = image[i - 1][j].rgbtRed;
                tmp[0][1].rgbtGreen = image[i - 1][j].rgbtGreen;
                tmp[0][1].rgbtBlue = image[i - 1][j].rgbtBlue;

                tmp[0][2].rgbtRed = image[i - 1][j + 1].rgbtRed;
                tmp[0][2].rgbtGreen = image[i - 1][j + 1].rgbtGreen;
                tmp[0][2].rgbtBlue = image[i - 1][j + 1].rgbtBlue;

                tmp[1][0].rgbtRed = image[i][j - 1].rgbtRed;
                tmp[1][0].rgbtGreen = image[i][j - 1].rgbtGreen;
                tmp[1][0].rgbtBlue = image[i][j - 1].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[1][2].rgbtRed = image[i][j + 1].rgbtRed;
                tmp[1][2].rgbtGreen = image[i][j + 1].rgbtGreen;
                tmp[1][2].rgbtBlue = image[i][j + 1].rgbtBlue;


                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;



            }

            else // no edges or corners
            {

                tmp[0][0].rgbtRed = image[i - 1][j - 1].rgbtRed;
                tmp[0][0].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                tmp[0][0].rgbtBlue = image[i - 1][j - 1].rgbtBlue;

                tmp[0][1].rgbtRed = image[i - 1][j].rgbtRed;
                tmp[0][1].rgbtGreen = image[i - 1][j].rgbtGreen;
                tmp[0][1].rgbtBlue = image[i - 1][j].rgbtBlue;

                tmp[0][2].rgbtRed = image[i - 1][j + 1].rgbtRed;
                tmp[0][2].rgbtGreen = image[i - 1][j + 1].rgbtGreen;
                tmp[0][2].rgbtBlue = image[i - 1][j + 1].rgbtBlue;

                tmp[1][0].rgbtRed = image[i][j - 1].rgbtRed;
                tmp[1][0].rgbtGreen = image[i][j - 1].rgbtGreen;
                tmp[1][0].rgbtBlue = image[i][j - 1].rgbtBlue;

                tmp[1][1].rgbtRed = image[i][j].rgbtRed;
                tmp[1][1].rgbtGreen = image[i][j].rgbtGreen;
                tmp[1][1].rgbtBlue = image[i][j].rgbtBlue;

                tmp[1][2].rgbtRed = image[i][j + 1].rgbtRed;
                tmp[1][2].rgbtGreen = image[i][j + 1].rgbtGreen;
                tmp[1][2].rgbtBlue = image[i][j + 1].rgbtBlue;

                tmp[2][0].rgbtRed = image[i + 1][j - 1].rgbtRed;
                tmp[2][0].rgbtGreen = image[i + 1][j - 1].rgbtGreen;
                tmp[2][0].rgbtBlue = image[i + 1][j - 1].rgbtBlue;

                tmp[2][1].rgbtRed = image[i + 1][j].rgbtRed;
                tmp[2][1].rgbtGreen = image[i + 1][j].rgbtGreen;
                tmp[2][1].rgbtBlue = image[i + 1][j].rgbtBlue;

                tmp[2][2].rgbtRed = image[i + 1][j + 1].rgbtRed;
                tmp[2][2].rgbtGreen = image[i + 1][j + 1].rgbtGreen;
                tmp[2][2].rgbtBlue = image[i + 1][j + 1].rgbtBlue;


                Mult(tmp, Gx, &xRed, &xGreen, &xBlue);
                Mult(tmp, Gy, &yRed, &yGreen, &yBlue);

                int red = round((float)sqrt(pow(xRed, 2) + pow(yRed, 2)));
                int green = round((float)sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
                int blue = round((float)sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

                regulate(&red);
                regulate(&green);
                regulate(&blue);

                newimage[i][j].rgbtRed = red;
                newimage[i][j].rgbtGreen = green;
                newimage[i][j].rgbtBlue = blue;

            }

        }

    }

    //copying the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue;
        }
    }








    return;
}
void Mult(RGBTRIPLE a[3][3], int b[3][3], int *zRed, int *zGreen, int *zBlue)
{
    *zRed = 0;
    *zGreen = 0;
    *zBlue = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            *zRed += a[i][j].rgbtRed * b[i][j];
            *zGreen += a[i][j].rgbtGreen * b[i][j];
            *zBlue += a[i][j].rgbtBlue * b[i][j];
        }
    }
    return;
}
void regulate(int *pixel)
{
    int a = *pixel;
    if (a > 255)
    {
        *pixel = 255;
    }
    return;
}