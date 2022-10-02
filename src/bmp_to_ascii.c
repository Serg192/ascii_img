#include "../inc/bmp_to_ascii.h"

static inline void print_usage(){
    const char *usage = "usage: ./bmp_to_ascii <image> <scale>";
    printf("%s\n", usage);
}

static inline int get_gradient_index(int val, const int gradient_size){
    const int max_v = 225 * 3;
    
    float per = val * 100 / max_v * 1.0f;

    int res = (gradient_size - 1) * per / 100;
    
    return res;
}

static inline char process_pixel(t_image_data *data,
                            int y,
                            int x, 
                            const int pix_per_w_ascii, 
                            const int pix_per_h_ascii){
    const char *gradient = " .,:!/r(l1Z4H9W8$@\0";
    const int gradient_size = strlen(gradient);
    const int start_X = x * pix_per_w_ascii;
    const int start_Y = y * pix_per_h_ascii;

    int average = 0;
    int count = pix_per_w_ascii * pix_per_h_ascii;

    for(int i = start_Y; i < start_Y + pix_per_h_ascii; i++){
        for(int j = start_X; j < start_X + pix_per_w_ascii; j++){
            average += (int)(data->pixels[i][j].r + data->pixels[i][j].g + data->pixels[i][j].b);
        }
    }
    
    average = average / count;

    char c = gradient[get_gradient_index(average, gradient_size)];

    return c == NULL ? 'Z' : c;
}

static void process_img(t_image_data *data, const float scale){
    const float ascii_aspect_ratio = 11.0f / 24.0f;
    const int w_ascii_count = data->width * scale;
    const int h_ascii_count = data->height * scale * ascii_aspect_ratio;
    const int pix_per_w_ascii = data->width / w_ascii_count;
    const int pix_per_h_ascii = data->height / h_ascii_count;

    char ascii_pixels[h_ascii_count][w_ascii_count];

    for(int i = 0; i < h_ascii_count; i++){
        for(int j = 0; j < w_ascii_count; j++){
            ascii_pixels[i][j] = process_pixel(data, i, j, pix_per_w_ascii, pix_per_h_ascii);
            printf("%c", ascii_pixels[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    if(argc != 3)
        print_usage();
    else{
        float scale = atof(argv[2]);
        t_image_data* img_data = mx_read_image(argv[1]);
        process_img(img_data, scale);
        
        mx_del_image_data(img_data);
    }
}
