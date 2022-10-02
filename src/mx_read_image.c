#include "../inc/bmp_to_ascii.h"

static void read_bmp_header(FILE *fp, t_bmp_header *header){
    fread(&(header->bfType), 2, 1, fp);
    fread(&(header->bfSize), sizeof(int), 1, fp);
    fread(&(header->bfReserved), sizeof(int), 1, fp);
    fread(&(header->bfOffBits), sizeof(int), 1, fp);    
}

static bool can_process(t_bmp_header *b_header, t_dib_header *d_header){
    
    if(b_header->bfType[0] != 'B' || b_header->bfType[1] != 'M')
        return false;
    if(d_header->compression != 0 || d_header->bitperpixel != 24)
        return false;
    return true;
}

static void read_img_pixel_data(FILE* fp, t_image_data *data){
   data->pixels = (t_BGR**)malloc(sizeof(void*) * data->height);
   
   for(int i = data->height - 1; i >= 0; i--){
       data->pixels[i] = (t_BGR*)malloc(sizeof(t_BGR) * data->width);
       fread(data->pixels[i], data->width, sizeof(t_BGR), fp);       
   } 
}

void mx_del_image_data(t_image_data *data){
    for(int i = 0; i < data->height; i++)
        free(data->pixels[i]);
    free(data->pixels);
    free(data);
}

t_image_data *mx_read_image(const char *filepath){
    t_image_data *data = malloc(sizeof(t_image_data));
    t_bmp_header bmp_header;
    t_dib_header dib_header;

    FILE *fp = fopen(filepath, "rb");

    if(fp == NULL){
        fprintf(stderr, "Can't open file: %s\n", filepath);
        exit(-1);
    }
    
    read_bmp_header(fp, &bmp_header);
    fread(&dib_header, sizeof(t_dib_header), 1, fp);
    if(!can_process(&bmp_header, &dib_header)){
        fprintf(stderr, "Can't process image: %s\n", filepath);
        fclose(fp);
        exit(-1);
    }
    fseek(fp, bmp_header.bfOffBits, SEEK_SET);
    data->width = dib_header.im_width;
    data->height = dib_header.im_height;

    read_img_pixel_data(fp, data);
    
    fclose(fp);
    return data;
}

