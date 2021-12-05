#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define n 5

int a[n], b[n],c[n],x=5;
int main(){
        int i,j;
        for(i=0;i<n;i++){
            a[i]=rand()%10;
            b[i]=rand()%10;
            }
        for(i=0;i<n;i++){
            printf("%d\t",a[i]);
            //printf("\n");
            printf("%d\t",b[i]);
            //printf("\n");
        }
        omp_set_num_threads(4);
        #pragma omp parallel for
         for(i=0;i<n;i++){
         int id=omp_get_thread_num();
         c[i]=(x*a[i])+b[i];
         printf("thread id=%d and c[%d]=%d\n",id,i,c[i]);
        
}
}
