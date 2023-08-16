#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Iterating on pixels
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            float average = 0.0; //Variable to average values
            average = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0); //Averaging operation
            //Reasignating values per color
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Iteration on each pixel
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width / 2; w ++)
        {
            //Swaping values
            RGBTRIPLE tmp = image[h][w]; //Declaring variable temp and asignating value
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Iteration on each pixel
    RGBTRIPLE buffer[height][width];

    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            //Kernel
            double avRed = 0.0, avGreen = 0.0, avBlue = 0.0;
            int pix_c = 0.0;

            //Left Upper corner    [h-1][w-1]
            if (h - 1 >= 0 && w - 1 >= 0)
            {

                avRed += image[h - 1][w - 1].rgbtRed;
                avGreen += image[h - 1][w - 1].rgbtGreen;
                avBlue += image[h - 1][w - 1].rgbtBlue;
                pix_c ++;

            }
            //Upper Edge    [h-1][w]
            if (h - 1 >= 0 && w >= 0 && w < width)
            {

                avRed += image[h - 1][w].rgbtRed;
                avGreen += image[h - 1][w].rgbtGreen;
                avBlue += image[h - 1][w].rgbtBlue;
                pix_c ++;
            }
            //Right Upper corner    [h-1][w+1]
            if (h - 1 >= 0 && w + 1 < width)
            {
                avRed += image[h - 1][w + 1].rgbtRed;
                avGreen += image[h - 1][w + 1].rgbtGreen;
                avBlue += image[h - 1][w + 1].rgbtBlue;
                pix_c ++;
            }

            //Left edge  [h][w-1]
            if (h >= 0 && h < height && w - 1 >= 0)
            {
                avRed += image[h][w - 1].rgbtRed;
                avGreen += image[h][w - 1].rgbtGreen;
                avBlue += image[h][w - 1].rgbtBlue;
                pix_c ++;
            }

            //Middle Pixel      [h][w]
            avRed += image[h][w].rgbtRed;
            avGreen += image[h][w].rgbtGreen;
            avBlue += image[h][w].rgbtBlue;
            pix_c ++;

            //Right edge    [h][w+1]
            if (h >= 0 && h < height && w + 1 < width)
            {
                avRed += image[h][w + 1].rgbtRed;
                avGreen += image[h][w + 1].rgbtGreen;
                avBlue += image[h][w + 1].rgbtBlue;
                pix_c ++;
            }

            //Left Lower corner  [h+1][w-1]
            if (h + 1 < height && w - 1 >= 0)
            {
                avRed += image[h + 1][w - 1].rgbtRed;
                avGreen += image[h + 1][w - 1].rgbtGreen;
                avBlue += image[h + 1][w - 1].rgbtBlue;
                pix_c ++;
            }

            //Lower edge    [h+1][w]
            if (h + 1 < height && w >= 0 && w < width)
            {
                avRed += image[h + 1][w].rgbtRed;
                avGreen += image[h + 1][w].rgbtGreen;
                avBlue += image[h + 1][w].rgbtBlue;
                pix_c ++;
            }

            //Right Lower corner   [h+1][w+1]
            if (h + 1 < height && w + 1 < width)
            {
                avRed += image[h + 1][w + 1].rgbtRed;
                avGreen += image[h + 1][w + 1].rgbtGreen;
                avBlue += image[h + 1][w + 1].rgbtBlue;
                pix_c ++;
            }

            buffer[h][w].rgbtRed = round(avRed / pix_c);
            buffer[h][w].rgbtGreen = round(avGreen / pix_c);
            buffer[h][w].rgbtBlue = round(avBlue / pix_c);
        }
    }
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            image[h][w] = buffer[h][w];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];


    int max = 255;
    //Iteration trough image
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            //Kernel Variables Declaration
            double gxRed = 0.0, gxGreen = 0.0, gxBlue = 0.0;
            double gyRed = 0.0, gyGreen = 0.0, gyBlue = 0.0;

            //Left Upper corner    [h-1][w-1]
            if (h - 1 >= 0 && w - 1 >= 0)
            {
                //Gx Kernel
                gxRed += image[h - 1][w - 1].rgbtRed * -1.0;
                gxGreen += image[h - 1][w - 1].rgbtGreen * -1.0;
                gxBlue += image[h - 1][w - 1].rgbtBlue * -1.0;
                //Gy Kernel
                gyRed += image[h - 1][w - 1].rgbtRed * -1.0;
                gyGreen += image[h - 1][w - 1].rgbtGreen * -1.0;
                gyBlue += image[h - 1][w - 1].rgbtBlue * -1.0;
            }

            //Upper Edge    [h-1][w]
            if (h - 1 >= 0 && w >= 0 && w < width)
            {
                //Gx Kernel
                gxRed += image[h - 1][w].rgbtRed * 0.0;
                gxGreen += image[h - 1][w].rgbtGreen * 0.0;
                gxBlue += image[h - 1][w].rgbtBlue * 0.0;
                //Gy Kernel
                gyRed += image[h - 1][w].rgbtRed * -2.0;
                gyGreen += image[h - 1][w].rgbtGreen * -2.0;
                gyBlue += image[h - 1][w].rgbtBlue * -2.0;
            }
            //Right Upper corner    [h-1][w+1]
            if (h - 1 >= 0 && w + 1 < width)
            {
                //Gx Kernel
                gxRed += image[h - 1][w + 1].rgbtRed * 1.0;
                gxGreen += image[h - 1][w + 1].rgbtGreen * 1.0;
                gxBlue += image[h - 1][w + 1].rgbtBlue * 1.0;
                //Gy Kernel
                gyRed += image[h - 1][w + 1].rgbtRed * -1.0;
                gyGreen += image[h - 1][w + 1].rgbtGreen * -1.0;
                gyBlue += image[h - 1][w + 1].rgbtBlue * -1.0;
            }

            //Left edge  [h][w-1]
            if (h >= 0 && h < height && w - 1 >= 0)
            {
                //Gx Kernel
                gxRed += image[h][w - 1].rgbtRed * -2.0;
                gxGreen += image[h][w - 1].rgbtGreen * -2.0;
                gxBlue += image[h][w - 1].rgbtBlue * -2.0;
                //Gy Kernel
                gyRed += image[h][w - 1].rgbtRed * 0.0;
                gyGreen += image[h][w - 1].rgbtGreen * 0.0;
                gyBlue += image[h][w - 1].rgbtBlue * 0.0;
            }

            //Middle Pixel      [h][w]
            //Gx Kernel
            gxRed += image[h][w].rgbtRed * 0.0;
            gxGreen += image[h][w].rgbtGreen * 0.0;
            gxBlue += image[h][w].rgbtBlue * 0.0;
            //Gy Kernel
            gyRed += image[h][w].rgbtRed * 0.0;
            gyGreen += image[h][w].rgbtGreen * 0.0;
            gyBlue += image[h][w].rgbtBlue * 0.0;

            //Right edge    [h][w + 1]
            if (h >= 0 && h < height && w + 1 < width)
            {
                gxRed += image[h][w + 1].rgbtRed * 2.0;
                gxGreen += image[h][w + 1].rgbtGreen * 2.0;
                gxBlue += image[h][w + 1].rgbtBlue * 2.0;
                //Gy Kernel
                gyRed += image[h][w + 1].rgbtRed * 0.0;
                gyGreen += image[h][w + 1].rgbtGreen * 0.0;
                gyBlue += image[h][w + 1].rgbtBlue * 0.0;
            }

            //Left Lower corner  [h + 1][w - 1]
            if (h + 1 < height && w - 1 >= 0)
            {
                gxRed += image[h + 1][w - 1].rgbtRed * -1.0;
                gxGreen += image[h + 1][w - 1].rgbtGreen * -1.0;
                gxBlue += image[h + 1][w - 1].rgbtBlue * -1.0;
                //Gy Kernel
                gyRed += image[h + 1][w - 1].rgbtRed * 1.0;
                gyGreen += image[h + 1][w - 1].rgbtGreen * 1.0;
                gyBlue += image[h + 1][w - 1].rgbtBlue * 1.0;
            }

            //Lower edge    [h + 1][w]
            if (h + 1 < height && w >= 0 && w < width)
            {
                gxRed += image[h + 1][w].rgbtRed * 0.0;
                gxGreen += image[h + 1][w].rgbtGreen * 0.0;
                gxBlue += image[h + 1][w].rgbtBlue * 0.0;
                //Gy Kernel
                gyRed += image[h + 1][w].rgbtRed * 2.0;
                gyGreen += image[h + 1][w].rgbtGreen * 2.0;
                gyBlue += image[h + 1][w].rgbtBlue * 2.0;
            }

            //Right Lower corner   [h + 1][w + 1]
            if (h + 1 < height && w + 1 < width)
            {
                gxRed += image[h + 1][w + 1].rgbtRed * 1.0;
                gxGreen += image[h + 1][w + 1].rgbtGreen * 1.0;
                gxBlue += image[h + 1][w + 1].rgbtBlue * 1.0;
                //Gy Kernel
                gyRed += image[h + 1][w + 1].rgbtRed * 1.0;
                gyGreen += image[h + 1][w + 1].rgbtGreen * 1.0;
                gyBlue += image[h + 1][w + 1].rgbtBlue * 1.0;
            }

            //Computig values and saving into a buffer
            buffer[h][w].rgbtRed = fmin(round(sqrt((gxRed * gxRed) + (gyRed * gyRed))), max);
            buffer[h][w].rgbtGreen = fmin(round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen))), max);
            buffer[h][w].rgbtBlue = fmin(round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue))), max);
        }
    }

    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            image[h][w] = buffer[h][w];
        }
    }
    return;
}
