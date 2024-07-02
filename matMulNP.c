#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include<stdlib.h>

void MatrixMul(float *a, uint32_t N0, float *b, uint32_t M0, uint32_t M1, float *f){
    for(uint32_t r=0;r<N0;r++){
        for(uint32_t c=0;c<M1;c++){
            for(uint32_t col=0;col<M0;col++){
                f[r*M1+c]+=a[r*M0+col]*b[col*M1+c];
            }
        }
    }
}

void initialize(float *a,uint32_t n,uint32_t m){
    for(uint32_t y=0;y<n;y++){
        for(uint32_t x=0;x<m;x++){
            a[y*m+x]=2;
        }
    }
}

void initialize_zero(float *a,uint32_t n,uint32_t m){
    for(uint32_t y=0;y<n;y++){
        for(uint32_t x=0;x<m;x++){
            a[y*m+x]=0;
        }
    }
}

void display(float *a,uint32_t n,uint32_t m){
    for(uint32_t y=0;y<n;y++){
        for(uint32_t x=0;x<m;x++){
            printf("%f ",a[y*m+x]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    clock_t start,end;
    double Etime;
    uint32_t N0=1000;
    uint32_t M0=2;
    uint32_t N1=2;
    uint32_t M1=10010;
    size_t zeroth = N0*M0*(sizeof(float));
    size_t first = N1*M1*(sizeof(float));
    size_t second = N0*M1*(sizeof(float));
    float *mat0,*mat1,*mat2;
    mat0=(float*)malloc(zeroth);
    mat1=(float*)malloc(first);
    mat2=(float*)malloc(second);
    initialize(mat0,N0,M0);
    initialize(mat1,N1,M1);
    initialize_zero(mat2,N0,M1);
    // display(mat0,N0,M0);
    // display(mat1,N1,M1);
    start=clock();
    MatrixMul(mat0,N0,mat1,M0,M1,mat2);
    end=clock();
    // display(mat2,N0,M1);
    Etime=((double)(end-start))/CLOCKS_PER_SEC;
    printf("execution time: %lf",Etime);
    return 0;
}
