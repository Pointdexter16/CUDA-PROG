#include<stdio.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<time.h>

#define N 256*9999

void ini(double *A,double val){
    for(int i=0;i<N;i++){
        A[i]=val;
    }
}

__global__ 
void addVector(double* a,double* b, double *c){
    int i=blockDim.x * blockIdx.x + threadIdx.x;
    if(i<N){
        c[i]=a[i]+b[i];
    }
}

int main(){

    clock_t start,end;
    double time;

    size_t bytes = N*sizeof(double);

    double *A = (double*)malloc(bytes);
    double *B = (double*)malloc(bytes);
    double *C = (double*)malloc(bytes);
    
    ini(A,1);
    ini(B,2);

    double *d_a,*d_b,*d_c;
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);

    cudaMemcpy(d_a, A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, B, bytes, cudaMemcpyHostToDevice);

    int thread=256;
    int block=ceil(float(N)/256);

    start=clock();
    addVector<<< block, thread >>>(d_a,d_b,d_c);
    end=clock();

    cudaMemcpy(C, d_c, bytes, cudaMemcpyDeviceToHost);

    printf("%lf + %lf=%lf",A[0],B[0],C[0]);

    free(A);
    free(B);
    free(C);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    printf("\n---------------------------\n");
	printf("__SUCCESS__\n");
	printf("---------------------------\n");
	printf("N                 = %d\n", N);
	printf("Threads Per Block = %d\n", thread);
	printf("Blocks In Grid    = %d\n", block);
	printf("---------------------------\n\n");

    time=(double(end-start))/CLOCKS_PER_SEC;
    printf("execution time: %lf",time);
    return 0;
}