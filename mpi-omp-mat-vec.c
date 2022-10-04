#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <math.h>

#define ROOT_PROC 0

/*
Assume a square matrix and that both the dimensions as well as 
the number of processes are powers of two; furthermore, they are 
just known at runtime.
*/

void printArr(int *arr, int n){
    int i, size = n;

    printf("[ ");
    for(i = 0; i < size; i++){
        if(i == size-1){
            printf("%d ", *(arr+i));
        }else{
            printf("%d, ", *(arr+i));
        }
    }
    printf("]\n");
}


int *createMatrix(int rows, int cols){
    int *matrix;
    int size = rows * cols * sizeof(int);

    matrix = (int *) malloc (size);
    return matrix;
}

void goldenReference(int *A, int* V, int N){
    int tmp, i, j;
    int ans[N];
    for(i = 0; i < N; i++){
        tmp = 0;
        for(j = 0; j < N; j++){
            tmp += A[(i * N) + j] * V[j];
        }
        ans[i] = tmp;
    }

    printf("Golden Reference: ");
    printArr(ans, N);
}

void matrixVectorProduct(int *submatrix, int* V, int N, int size){
    int tmp, i, j;
    
    for(i = 0; i < size/N; i++){
        tmp = 0;
        #pragma omp parallel for reduction(+:tmp)
        for(j = 0; j < N; j++){
            tmp += submatrix[(i * N) + j] * V[j];
        }
        submatrix[i] = tmp;
    }
}

int isPowerOfTwo(int n){
    while(n != 1){
        if(n & 1)
            return 0;
        n = n >> 1;
    }
    return 1;
}

int main( int argc, char *argv[] ){

    int *A, *V, *ans;
    int N, i, j, p, my_rank, size;

    MPI_Init ( &argc, &argv );
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank );

    if(my_rank == 0){

        scanf("%d", &N);
        // N % p means that the row matrix size is divisible by the number of processes.
        if(N < 1 || !isPowerOfTwo(N) || N % p != 0) return 0; 

        A = createMatrix(N, N);
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                scanf("%d", &A[i * N + j]);
            }
        }

        V = malloc(N * sizeof(int));
        for(i = 0; i < N; i++){
            scanf("%d", &V[i]);
        }

        ans = malloc(N * sizeof(int));

    }

    MPI_Bcast (&N, 1, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);

    size = (N*N)/p;

    MPI_Bcast (V, N, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);
    
    int *submatrix = NULL;
    submatrix = ( int * ) malloc ( sizeof ( int ) * size );

    MPI_Scatter (A, size, MPI_INT, submatrix, size, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);

    matrixVectorProduct(submatrix, V, N, size);
    
    MPI_Gather(submatrix, size/N, MPI_INT, ans, size/N, MPI_INT, ROOT_PROC, MPI_COMM_WORLD);

    if(my_rank == ROOT_PROC){
        goldenReference(A, V, N);
        printf("MPI Result:       ");
        printArr(ans, N);
        free(ans);
        free(V);
        free(A);
    }

    free(submatrix);
    
    MPI_Finalize();

    return 0;

}
