#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 50

using namespace std;

void read_matrix(int matrix[MAX_SIZE][MAX_SIZE], const char *filename, int size);
void write_matrix(int matrix[MAX_SIZE][MAX_SIZE], const char *filename, int size);
void multiply(int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int C[MAX_SIZE][MAX_SIZE], int size);

int main(){
    int matrixA[MAX_SIZE][MAX_SIZE], matrixB[MAX_SIZE][MAX_SIZE], matrixC[MAX_SIZE][MAX_SIZE];
    read_matrix(matrixA, "C:\\Users\\randy\\Documents\\Coding\\CPP_File\\matrixA.txt", 3);
    read_matrix(matrixB, "C:\\Users\\randy\\Documents\\Coding\\CPP_File\\matrixB.txt", 3);
    multiply(matrixA, matrixB, matrixC, 3);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }
    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < 3; j++){
    //         printf("%d ", matrixB[i][j]);
    //     }
    //     printf("\n");
    // }
}

void read_matrix(int matrix[MAX_SIZE][MAX_SIZE], const char *filename, int size){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(fscanf(file, "%d", &matrix[i][j]) != 1){
                perror("Error reading matrix");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
}

void write_matrix(int matrix[MAX_SIZE][MAX_SIZE], const char *filename, int size){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void multiply(int A[MAX_SIZE][MAX_SIZE], int B[MAX_SIZE][MAX_SIZE], int C[MAX_SIZE][MAX_SIZE], int size){
    #pragma omp parallel for collapse(2) schedule(static) num_threads(8)
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int sum = 0;
            #pragma omp parallel for schedule(static) num_threads(8) reduction(+:sum)
            for(int k = 0; k < size; k++){
                sum += (A[i][k]*B[k][j]);
            }
            C[i][j] = sum;
        }
    }
}
