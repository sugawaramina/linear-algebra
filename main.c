#include "matrix.h"

int main() {
    // 创建两个 2×2 矩阵
    Matrix *A = create_matrix(2, 2);
    Matrix *B = create_matrix(2, 2);
    
    // 手动赋值（后续可以写 set_value 函数）
    A->data[0][0] = 1; A->data[0][1] = 2;
    A->data[1][0] = 3; A->data[1][1] = 4;
    
    B->data[0][0] = 5; B->data[0][1] = 6;
    B->data[1][0] = 7; B->data[1][1] = 8;
    
    printf("A:\n"); print_matrix(A);
    printf("B:\n"); print_matrix(B);
    
    Matrix *C = mat_add(A, B);
    printf("A+B:\n"); print_matrix(C);
    
    Matrix *D = mat_mul(A, B);
    printf("A*B:\n"); print_matrix(D);
    
    // 释放所有矩阵
    free_matrix(A); free_matrix(B);
    free_matrix(C); free_matrix(D);
    
    return 0;
}