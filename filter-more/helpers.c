#include "helpers.h"
#include <math.h>

float rounded(float number);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int total = image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen;
            float mean = total / 3.0;
            image[i][j].rgbtRed = round(mean);
            image[i][j].rgbtBlue = round(mean);
            image[i][j].rgbtGreen = round(mean);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image2[i][j] = image[i][j];
        }
        for(int j = 0, k = width-1; j < width && k>=0; j++, k--){
            image[i][j] = image2[i][k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
     for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image2[i][j] = image[i][j];
        }
     }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int count = 0;
            float sumRed, sumBlue, sumGreen;
            sumRed = sumBlue = sumGreen = 0;
            for(int k = i - 1; k <= i + 1; k++){
                if(k < 0||k >= height) continue;
                for(int l = j - 1; l <= j + 1; l++){
                    if(l < 0||l >= width) continue;
                    sumRed += image2[k][l].rgbtRed;
                    sumBlue += image2[k][l].rgbtBlue;
                    sumGreen += image2[k][l].rgbtGreen;
                    count++;
                }
            }
            image[i][j].rgbtRed = round(sumRed/count);
            image[i][j].rgbtBlue = round(sumBlue/count);
            image[i][j].rgbtGreen = round(sumGreen/count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image2[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int xred, xblue, xgreen, yred, yblue, ygreen;
            xred = xblue = xgreen = yred = yblue = ygreen = 0;
            float sumRed, sumBlue, sumGreen;
            for(int k = i - 1; k <= i + 1; k++){
                if(k < 0||k >= height) continue;
                for(int l = j - 1; l <= j + 1; l++){
                    int kernelx = 1, kernely = 1;
                    if(l < 0||l >= width) continue;
                    if(j - l == 0){
                        kernelx = 0;
                        kernely *=2;
                    }
                    if(i - k == 0){
                        kernely = 0;
                        kernelx *= 2;
                    }
                    if(j - l == 1) kernelx *= -1;
                    if(i - k == 1) kernely *= -1;
                    xred += kernelx * image2[k][l].rgbtRed;
                    xblue += kernelx * image2[k][l].rgbtBlue;
                    xgreen += kernelx * image2[k][l].rgbtGreen;
                    yred += kernely * image2[k][l].rgbtRed;
                    yblue += kernely * image2[k][l].rgbtBlue;
                    ygreen += kernely * image2[k][l].rgbtGreen;
                }
            }
            sumRed = sqrt(pow(xred, 2) + pow(yred, 2));
            sumBlue = sqrt(pow(xblue, 2) + pow(yblue, 2));
            sumGreen = sqrt(pow(xgreen, 2) + pow(ygreen, 2));
            image[i][j].rgbtRed = rounded(sumRed);
            image[i][j].rgbtBlue = rounded(sumBlue);
            image[i][j].rgbtGreen = rounded(sumGreen);
        }
    }
    return;
}

float rounded(float number){
    if (number > 255) return 255;
    else return round(number);
}
