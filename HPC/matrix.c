#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



#define N 100

int A[N][N];
int B[N][N];
int C[N][N];

int main() 
{
    int i,j,k;
    omp_set_num_threads(omp_get_num_procs());
    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
	{
            A[i][j] = rand() % 100 + 1;
            B[i][j] = rand() % 100 + 1;
	}
    double start = omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(A,B,C)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }


    double end = omp_get_wtime(); 
    for (i= 0; i< N; i++){
    printf("\n"); 
        for (j= 0; j< N; j++)
	{
            printf("%d\n",A[i][j]);
            
           
            
            //printf("%d\n",C[i][j]);   
	} 
	}
	for (i= 0; i< N; i++){
	printf("\n"); 
	for (j= 0; j< N; j++){
	 printf("%d\n",B[i][j]);
	}
	}
	 for (i= 0; i< N; i++){
	 printf("\n"); 
        for (j= 0; j< N; j++)
	{
	printf("%d\n",C[i][j]);
	}
	}
    double elapsed = end - start;
    printf("elapsed time = %f seconds.\n", elapsed);
    }
