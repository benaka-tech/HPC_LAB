#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h>  
void main ()
    {   int m,n,arr2[100],sum=0;
        m=rand() % 10 + 1;
        printf("the number of section=%d\n",m);
        n=rand() % 100 + 1;
        printf("the number of items=%d\n",n);
        int arr[m][n],i,j;     
        for (i=0;i<m;i++)    
        {    
            for (j=0;j<n;j++)    
            {              
                arr[i][j]=rand() % 1000 + 1;
            }    
        }    
        printf("\n printing the elements ....\n");     
        for(i=0;i<m;i++)    
        {    
            printf("\n");    
            for (j=0;j<n;j++)    
            {   printf("Enter a[%d][%d]: %d\n ",i,j,arr[i][j]); 
                //printf("%d\t",arr[i][j]);    
            }    
        }
        double start = omp_get_wtime();
        #pragma omp parallel for
        for(int i = 0; i < m; i++){  
        int sumCol = 0;  
        for(int j = 0; j < n; j++){  
          sumCol = sumCol + arr[i][j];  
        } 
        printf("\nSum of %d column: %d\n", (i+1), sumCol);  
          arr2[i] = sumCol;
    }
    #pragma omp critical
    for(int i = 0; i < m; i++){ 
    printf("%d\n",arr2[i]);
    sum += arr2[i];
    }
    double end = omp_get_wtime(); 
    printf("\nTotal Bill %d\n",sum);
    double elapsed = end - start;
    printf("elapsed time = %f seconds.\n", elapsed);
    }    
