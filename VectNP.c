#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void vecAdd(float* a,float* b,float* c,int n){
    for(int i=0;i<n;i++){
        c[i]=a[i]+b[i];
    }
}

void ini(float* a, int n){
    for(int i=0;i<n;i++){
        a[i]=i+1;
    }
}

void display(float* a,int n){
    for(int i=0;i<n;i++){
        printf("%f ",a[i]);
    }
    printf("\n");
}

int main(){
    clock_t start,end;
    double Etime;
    float *a,*b,*c;
    int n=10485760;
    a=(float*)malloc(n*sizeof(float));
    b=(float*)malloc(n*sizeof(float));
    c=(float*)malloc(n*sizeof(float));
    ini(a,n);
    ini(b,n);
    display(a,1);
    display(b,1);
    start=clock();
    vecAdd(a,b,c,n);
    end=clock();
    display(c,1);
    Etime=((double)(end-start))/CLOCKS_PER_SEC;
    printf("execution time: %lf",Etime);
    return 0;
}