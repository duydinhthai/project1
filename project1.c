#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "C:/Users/HP/OneDrive - student.vgu.edu.vn/Second Year/Programming 1/PROJECT 1/headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "C:/Users/HP/OneDrive - student.vgu.edu.vn/Second Year/Programming 1/PROJECT 1/headers/stb_image_write.h"
/**
 * Create a new 1-dimensional array with the given size
 * @param[in] _size the size of the array
 * @param[out] _ empty 1-dimensional array filled with 0
 */
unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *change_background(unsigned char *image,unsigned char *image_background, unsigned char *image_foreground, int width, int height, int channel)
{
    //luu anh vao array
 

    unsigned char* array_image_foreground=uc_arrayNew_1d(width*height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                int sum=0;
                for (int k = 0; k < channel; k++)
                {
                     sum = sum + abs(image_background[i * width * channel + j * channel + k]-image_foreground[i * width * channel + j * channel + k]);
                }  
                if(sum<160)
                {
                    array_image_foreground[i * width + j ] = 0;
                }
                else
                {
                    array_image_foreground[i * width  + j ] = 255;
                }          
        }
    }
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                for (int k = 0; k < channel; k++)
                {
                    if( array_image_foreground[i * width + j ] == 255)
                    {
                        image[i * width * channel + j * channel + k]=image_foreground[i * width * channel + j * channel + k];
                    }
                }
        }
    }

    /*for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
                for (int k = 0; k < channel; ++k)
                {
                    if(image_background[i * width * channel + j * channel + k]==image_foreground[i * width * channel + j * channel + k])
                    {
                        if(k<channel1)
                        {
                    image_foreground[i * width * channel + j * channel + k]=image_background[i * width * channel + j * channel + k]-image_foreground[i * width * channel + j * channel + k];
                        }
                        
                    }
                }
        }
    }*/
    

    /*
     for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
                for (int k = 0; k < channel; k++)
                {
                    array_image_background[i * width * channel + j * channel + k] = image_background[i * width * channel + j * channel + k];
                    array_image_foreground[i * width * channel + j * channel + k] = image_foreground[i * width * channel + j * channel + k];
                }
        }
    }
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
                for (int k = 0; k < channel1; k++)
                {
                    array_image[i * width * channel1 + j * channel1 + k]=image[i * width * channel1 + j * channel1 + k];
                }
        }
    }
    */
   
    //so sanh foreground voi background -> neu bang nhau thi doi foreground tai vi tri do bang weatherforecast
    /*
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
                for (int k = 0; k < channel; k++)
                {
                    if( array_image_background[i * width * channel + j * channel + k]==array_image_foreground[i * width * channel + j * channel + k])
                    {
                        array_image_foreground[i * width * channel + j * channel + k]=0;
                    }
                }
        }
    }
    */
    return image;
}

int main()
{
    // declare variables
    int width, height, channel;
    int width1, height1, channel1;
    int width2, height2, channel2;
    char background_img[] = "./images/background.jpg";
    char foreground_img[] = "./images/foreground.jpg";
    char weather_forecast_img[]= "./images/new_background.jpg";
    char save_result[] = "./images/FINAL.png";

    // read image data
    unsigned char *image = stbi_load(background_img, &width, &height, &channel, 0);
    if (image == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    unsigned char *image1 = stbi_load(foreground_img, &width1, &height1, &channel1, 0);
    if (image1 == NULL)
    {
        printf("\nError in loading the image 1\n");
        exit(1);
    }
    unsigned char *image2 = stbi_load(weather_forecast_img, &width2, &height2, &channel2, 0);
    if (image2 == NULL)
    {
        printf("\nError in loading the image 2\n");
        exit(1);
    }
    
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);
    printf("Width1 = %d\nHeight1 = %d\nChannel1 = %d\n", width1, height1, channel1);
    printf("Width2 = %d\nHeight2 = %d\nChannel2 = %d\n", width2, height2, channel2);
    //change background
    unsigned char *new_image=change_background(image2, image, image1, width, height, channel);
    stbi_write_png(save_result, width, height, channel, new_image, width*channel);
    printf("New image saved to %s\n", save_result);
}

