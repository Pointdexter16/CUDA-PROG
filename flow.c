#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include<string.h>

#ifndef FLOW_C_
#define FLOW_C_
#endif 


#define return_defer(value) \
    do                      \
    {                       \
        result = (value);   \
        goto defer;         \
    } while (0)

typedef int Errno;

void flow_fill(uint32_t *pixels, size_t width, size_t heigth, uint32_t color)
{
    for (size_t i = 0; i < heigth * width; i++)
    {
        pixels[i] = color;
    }
}

Errno flow_save_to_ppm(uint32_t *pixels, size_t width, size_t heigth, const char *file_path)
{
    int result = 0;
    FILE *f = fopen(file_path, "wb");

    {
        if (f == NULL)
            return_defer(errno);
        fprintf(f, "P6\n%zu %zu 255\n", width, heigth);
        if (ferror(f))
            return_defer(errno);
        for (size_t i = 0; i < heigth * width; i++)
        {
            uint32_t pixel = pixels[i];
            uint8_t Bytes[3] = {
                (pixel >> (8 * 0)) & 0xFF,
                (pixel >> (8 * 1)) & 0xFF,
                (pixel >> (8 * 2)) & 0xFF,
            };
            fwrite(Bytes, sizeof(Bytes), 1, f);
        }
    }

defer:
    if (f)
        fclose(f);
    return result;
}

void flow_fill_rect(uint32_t *pixels, size_t pixel_width, size_t pixel_height, int x0, int y0, size_t w, size_t h, uint32_t color){
    int y,x;
    for(int dy=0; dy < (int)h; dy++){
        y = y0 + dy;
        if(0 <= y && y < (int)pixel_height){
            for(int dx=0; dx < (int)w; dx++){
                x = x0 + dx;
                if(0 <= x && x < (int)pixel_width){
                    pixels[y*pixel_width + x]=color;
                }   
            }
        }
    }
}

void flow_fill_circle(uint32_t *pixels, size_t pixel_width, size_t pixel_height, int cx, int cy, int r, uint32_t color){
    int x0=cx-r;
    int y0=cy-r;
    int x1=cx+r;
    int y1=cy+r;
    for(int y=y0;y<=y1;y++){
        if(0 <= y && y < (int)pixel_height){
            for(int x=x0;x<=x1;x++){
                if(0 <= x && x < (int)pixel_width){
                    int dx=x-cx;
                    int dy=y-cy;
                    if(dx*dx + dy*dy<=r*r){
                        pixels[pixel_width*y+x]=color;
                    }
                }
            }
        }
    }
}


