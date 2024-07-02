#include<cuda_runtime.h>
#include<cuda.h>
#include<stdio.h>
#include<time.h>

#define N 16


void initialize(float *a,int n,int m){
    for(int y=0;y<n;y++){
        for(int x=0;x<m;x++){
            a[y*m+x]=2;
        }
    }
}

void initialize_zero(float *a,int n,int m){
    for(int y=0;y<n;y++){
        for(int x=0;x<m;x++){
            a[y*m+x]=0;
        }
    }
}

void display(float *a,int n,int m){
    for(int y=0;y<n;y++){
        for(int x=0;x<m;x++){
            printf("%f ",a[y*m+x]);
        }
        printf("\n");
    }
    printf("\n");
}

__global__
void MatrixMull(float* a, int N0, int M0, float* b, int N1, int M1, float* c){
    int i=blockIdx.y*blockDim.y + threadIdx.y;
    int j=blockIdx.x*blockDim.x + threadIdx.x;
    float result=0;
    if((i<N0)&&(j<M1)){
        for(int k=0;k<N;k++){
            result+=a[i*N + k]*b[k*N + j];
        }
        c[i*N + j]=result;        
    }
}


int main(){ 
    clock_t start,end;
    double Etime;
    float *a,*b,*c;
    size_t byte=(16*16)*(sizeof(float));
    a=(float*)malloc(byte);
    b=(float*)malloc(byte);
    c=(float*)malloc(byte);
    initialize(a,16,N);
    initialize(b,N,16);
    initialize_zero(c,16,16);
    float *d_a,*d_b,*d_c;
    cudaMalloc(&d_a,byte);
    cudaMalloc(&d_b,byte);
    cudaMalloc(&d_c,byte);
    cudaMemcpy( d_a, a, byte, cudaMemcpyHostToDevice);
    cudaMemcpy( d_b, b, byte, cudaMemcpyHostToDevice);
    cudaMemcpy( d_c, c, byte, cudaMemcpyHostToDevice);
    dim3 blockDim(8,8,1);
    dim3 griddim(8,8,1);
    start=clock();
    MatrixMull<<< griddim, blockDim >>>(d_a, 16, N, d_b, 16, N, d_c);
    end=clock ();
    cudaMemcpy(c,d_c, byte, cudaMemcpyDeviceToHost);
    Etime=((double)(end-start))/CLOCKS_PER_SEC;
    printf("execution time: %lf",Etime);
    free(a);
    free(b);
    free(c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;   
}
