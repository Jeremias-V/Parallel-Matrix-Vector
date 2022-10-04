#include <stdio.h>
#include <stdlib.h>

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

int* matrixVectorProduct(int *A, int* V, int N){
    int tmp, i, j;
    int* ans = malloc(N * sizeof(int));
    for(i = 0; i < N; i++){
        tmp = 0;
        for(j = 0; j < N; j++){
            tmp += A[i * (N) + j] * V[j];
        }
        ans[i] = tmp;
    }
    return ans;
}

int main(){

    int M, N, P;
    int i, j;

    scanf("%d", &N);

    int * A = createMatrix(N, N);
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            scanf("%d", &A[i * N + j]);
        }
    }

    int * V = malloc(N * sizeof(int));
    for(i = 0; i < N; i++){
        scanf("%d", &V[i]);
    }

    int* ans = matrixVectorProduct(A, V, N);

    printArr(ans, N);
    free(ans);
    free(A);
    free(V);


    return 0;

}
