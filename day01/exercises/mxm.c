#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define SIZE_OF 8
#define SEED 86456

int main() {
    
    double x[N][N], y[N][N], z[N][N];
    int i, j, k, b,s;
    double msec, rate,start, finish;

    srand(time(NULL));

    // Initialize matrices x and y with random values
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            x[i][j] = ((double)rand() / RAND_MAX) + 1.0;
            y[i][j] = ((double)rand() / RAND_MAX) + 1.0;
            z[i][j] = 0.0;
        }
    }

    

    // Perform matrix multiplication
    start =  (double)clock() /(double) CLOCKS_PER_SEC;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                z[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    finish = (double)clock() /(double) CLOCKS_PER_SEC;
    

    // Calculate CPU time and bandwidth
    msec = ((double)(finish - start) * 1000.0) ;
    rate = (N*N*sizeof(double)*(1000/msec))/(1024*1024);
     // Output results
    printf("MXM not blocks : CPU Time = %f milliseconds, Bandwidth = %f GFLOPs\n", msec, rate);

    //Block version
     //Initialize matrice z = 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            z[i][j] = 0.0;
        }
    }
    
     printf("entrer blocsize :");
     scanf("%d",&b);
     s = 0;
     
    start =  (double)clock() /(double) CLOCKS_PER_SEC;
     for (int kk = 0; kk<N; kk+=b)
        for(int jj = 0; jj<N; jj+=b)
          for(int i = 0; i <N; i++)
              for(int j = jj; j<jj+b;j++)
                  {
                    s = z[i][j];
                     for (int k = kk; k<kk+b;k++)
                        s  = s + x[i][j]*y[k][j];
                          z[i][j] = s;
                  }
          finish = (double)clock() /(double) CLOCKS_PER_SEC;
      // Calculate CPU time and bandwidth.
    msec = ((double)(finish - start) * 1000.0) ;
    rate = (2*N*N*sizeof(double)*(1000.0/msec))/(1024*1024);
       // Output results
    printf("CPU Time = %f milliseconds, Bandwidth = %f GFLOPs\n", msec, rate);
    return 0;
   }