#include "flow.c"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 400
#define HEIGHT 400
#define BACKGROUND_COLOR 0xFF303030
#define FOREGROUND_COLOR 0xFF2020FF

static uint32_t pixels[WIDTH*HEIGHT];

struct CNumber{
    float r;
    float i;
};

struct CNumber add(struct CNumber a,struct CNumber b){
    struct CNumber result;
    result.r=a.r+b.r;
    result.i=a.i+b.i;
    return result;
}

struct CNumber mul(struct CNumber a,struct CNumber b){
    struct CNumber result;
    result.r=a.r*b.r-(a.i*b.i);
    result.i=a.r*b.i+a.i*b.r;
    return result;
}

void display(struct CNumber* a){
    printf("%d + %di",a->r,a->i);
}

float radius(struct CNumber* a){
    float result=sqrt(a->r*a->r + a->i*a->i);
    return result; 
}

void julieSetGenerator(){
    struct CNumber* ptr=;
}

void checker(struct CNumber* a,struct CNumber* c){
    int x,y;
    x=a->r*100+WIDTH/2;
    y=a->i*100+HEIGHT/2;
    struct CNumber* result = (struct CNumber*)malloc(sizeof(struct CNumber));   
    *result = *a;
    for(int i=0;i<100;i++){
        *result=add(mul(*result,*result),*c);
    }
    if(!radius(result)>1000){
        if((x<WIDTH && x>=0)||(y<HEIGHT && y>=0)){
            pixels[y*WIDTH+x]=0xFF2020FF;
        }
    }
    free(result);
}

int main(){
    struct CNumber* a=(struct CNumber*)malloc(sizeof(struct CNumber));   
    struct CNumber* b=(struct CNumber*)malloc(sizeof(struct CNumber));;
    flow_fill(pixels,WIDTH,HEIGHT,0xFF303030);

    a->r=5;
    a->i=1;
    b->r=4;
    b->i=2;

    display(a);

    return 0;
}