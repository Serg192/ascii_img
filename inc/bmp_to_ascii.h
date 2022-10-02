#ifndef BMP_TO_ASCII
#define BMP_TO_ASCII

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct s_bmp_header 
{
    char bfType[2];
    int bfSize;
    int bfReserved;
    int bfOffBits;
}              t_bmp_header;

typedef struct s_dib_header
{
    int header_size;
    int im_width;
    int im_height;
    short colorplanes;
    short bitperpixel;
    int compression;
    int im_size;
}              t_dib_header;

typedef struct s_BGR
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}              t_BGR;

typedef struct s_image_data
{
    int width;
    int height;
    t_BGR **pixels;
}              t_image_data;


t_image_data *mx_read_image(const char *filename);

void mx_del_image_data(t_image_data *data);

#endif
