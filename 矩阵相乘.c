#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/*将给定两个矩阵，实现矩阵常见运算，
 * 包括矩阵加法，矩阵乘法，矩阵转置
 * 对于矩阵乘法，用两种方式实现。
要求
能够生成大矩阵(行、列均超过100维)
能够正确实现矩阵加法
能够正确实现矩阵转置
能够正确实现矩阵乘法，打印运算时间
具有错误保护(无法相乘的两个矩阵相乘，提示错误)
能够使用分解方式实现之前的矩阵乘法，并打印运算时间
注:Strassen算法不要求递归，按照算法步骤实现即可:
 对普通乘法和Strassen算法自行选择合适的维度。*/
typedef struct {
    int row;//行
    int col;//列
    float **matrix;
}matrix;

// to create a matrix
void generateLargeMatrix(matrix *m ,int row ,int col)
{
    m->row = row;
    m->col = col;
    m->matrix = (float **) malloc(sizeof(float *)*m->row);
    for(int i = 0; i < m->row; i++){
        m->matrix[i] = (float *)malloc(sizeof(float)*m->col);
    }
    for (int i = 0; i < m->row; i++){
        for (int j = 0; j < m->col; j++) {
            // Initialize matrix
            m->matrix[i][j] = 0;
        }
    }
}

// to assign a matrix
void assignMatrix(matrix *m)
{
    srand(time(NULL));
    for (int i = 0; i < m->row; i++){
        for (int j = 0; j < m->col; j++) {
            // Initialize matrix
            m->matrix[i][j] = (float )(rand() % 10);
        }
    }
}

// to transpose a matrix
matrix transposeMatrix(matrix m)
{

    matrix result;
    generateLargeMatrix(&result,m.row,m.col);

    for(int i = 0; i < m.row; i++){
        for(int j = 0; j < m.col; j++){
            result.matrix[i][j] = m.matrix[j][i];
        }
    }
    return result;
}

// Addition
matrix add(matrix A ,matrix B)
{
    if(A.row != B.row || A.col != B.col){
        printf("size error, matrix A's column(row) doesn't equal to matrix B's column(row)");
        exit(0);
    }
    // 计算结果并返回
    matrix result;
    generateLargeMatrix(&result, A.row, A.col);
    for(int i = 0; i < result.row; ++i){
        for(int j = 0; j < result.col; ++j){
            result.matrix[i][j] += A.matrix[i][j] + B.matrix[i][j];
        }
    }
    return result;
}

// sub
matrix sub(matrix A, matrix B){
    // 判断矩阵A和矩阵B是否为同型矩阵
    if(A.row != B.row || A.col != B.col){
        printf("size error, matrix A's column(row) doesn't equal to matrix B's column(row)");
        exit(0);
    }
    // 计算结果并返回
    matrix result;
    generateLargeMatrix(&result, A.row, A.col);
    for(int i = 0; i < result.row; i++){
        for(int j = 0; j < result.col; j++){
            result.matrix[i][j] += A.matrix[i][j] - B.matrix[i][j];
        }
    }
    return result;
}

// Multiply
matrix multiply(matrix A,matrix B)
{
    if(A.col != B.row){
        printf("size error, matrix A's column doesn't equal to matrix B's row");
        exit(0);
    }
    // 计算结果并返回
    matrix result;
    clock_t start ,finish;
    double duration;
    printf("this method runs");
    start = clock();
    generateLargeMatrix(&result, A.row, B.col);
    for(int i = 0; i < result.row; i++){
        for(int j = 0; j < result.col; j++){
            for(int k = 0; k < A.col; k++){
                result.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
            }
        }
    }
    finish = clock();
    duration = (double )(finish - start) / CLOCKS_PER_SEC;
    printf("%f seconds",duration);
    system("pause");
    return result;
}

// strassen multiply
void strassen(matrix A, matrix B,matrix C)
{
    int n = A.col;
    matrix A11,A12,A21,A22,B11,B12,B21,B22,AA,BB,M1,M2,M3,M4,M5,M6,M7,MM1,MM2,C11,C22,C12,C21;
    generateLargeMatrix(&A11,A.col,A.col);
    generateLargeMatrix(&A12,A.col,A.col);
    generateLargeMatrix(&A21,A.col,A.col);
    generateLargeMatrix(&A22,A.col,A.col);
    generateLargeMatrix(&B11,A.col,A.col);
    generateLargeMatrix(&B12,A.col,A.col);
    generateLargeMatrix(&B21,A.col,A.col);
    generateLargeMatrix(&B22,A.col,A.col);
    generateLargeMatrix(&AA, n/2, n/2);
    generateLargeMatrix(&BB, n/2, n/2);
    generateLargeMatrix(&M1, n/2, n/2);
    generateLargeMatrix(&M2, n/2, n/2);
    generateLargeMatrix(&M3, n/2, n/2);
    generateLargeMatrix(&M4, n/2, n/2);
    generateLargeMatrix(&M5, n/2, n/2);
    generateLargeMatrix(&M6, n/2, n/2);
    generateLargeMatrix(&M7, n/2, n/2);
    generateLargeMatrix(&MM1, n/2, n/2);
    generateLargeMatrix(&MM2, n/2, n/2);
    generateLargeMatrix(&C11, n/2, n/2);
    generateLargeMatrix(&C22, n/2, n/2);
    generateLargeMatrix(&C12, n/2, n/2);
    generateLargeMatrix(&C21, n/2, n/2);

    if(n==2)
    {
        C = multiply(A,B);
    } else{
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n / 2; j++) {
                A11.matrix[i][j] = A.matrix[i][j];
                A12.matrix[i][j] = A.matrix[i][j + n / 2];
                A21.matrix[i][j] = A.matrix[i + n / 2][j];
                A22.matrix[i][j] = A.matrix[i + n / 2][j + n / 2];
                B11.matrix[i][j] = B.matrix[i][j];
                B12.matrix[i][j] = B.matrix[i][j + n / 2];
                B21.matrix[i][j] = B.matrix[i + n / 2][j];
                B22.matrix[i][j] = B.matrix[i + n / 2][j + n / 2];
            }
        }
        BB = sub(B12,B22);
        strassen(A11,BB,M1);
        AA = add(A11,A12);
        strassen(AA,B22,M2);
        AA = add(A21,A22);
        strassen(AA,B11,M3);
        BB = sub(B21,B11);
        strassen(A22,BB,M4);
        AA = add(A11,A22);
        BB = add(B11,B22);
        strassen(AA,BB,M5);
        AA = sub(A12,A22);
        BB = add(B21,B22);
        strassen(AA,BB,M6);
        AA = sub(A11,A21);
        BB = add(B11,B12);
        strassen(AA,BB,M7);
        MM1 = add(M5,M4);
        MM2 = sub(M2,M6);
        C11 = sub(MM1,MM2);
        C12 = add(M1,M2);
        C21 = add(M3,M4);
        MM1 = add(M5,M1);
        MM2 = add(M3,M7);
        C22 = sub(MM1,MM2);
        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n/2; j++) {
                C.matrix[i][j] = C11.matrix[i][j];
                C.matrix[i][j + n / 2] = C12.matrix[i][j];
                C.matrix[i + n / 2][j] = C21.matrix[i][j];
                C.matrix[i + n / 2][j + n / 2] = C22.matrix[i][j];
            }
        }
    }

}

// to print a matrix
void printMatrix(matrix m)
{
    for(int i = 0; i < m.row; i++){
        for(int j = 0; j < m.col; j++){
            printf("%f ", m.matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rowA,rowB,colA,colB;
    scanf("%d %d %d %d",&rowA,&colA,&rowB,&colB);
    matrix A,B;
    generateLargeMatrix(&A, rowA, colA);
    generateLargeMatrix(&B, rowB, colB);
    assignMatrix(&A);
    assignMatrix(&B);
    printf("A is equal to\n");
    printMatrix(A);
    printf("B is equal to\n");
    printMatrix(B);
    matrix addResult = add(A, B);
    matrix transposeResult = transposeMatrix(A);
    matrix multiResult = multiply(A, B);
    printf("addResult is equal to\n");
    printMatrix(addResult);
    printf("transposeResult is equal to\n");
    printMatrix(transposeResult);
    printf("multiResult is equal to\n");
    printMatrix(multiResult);
    matrix RES;
    strassen(A,B,RES);
    printMatrix(RES);
    return 0;
}
