#include "matrix.h"
#include <math.h>
#include <stdio.h>

int main() {
    printf("=== Matrix Inversion Test ===\n");
    
    // 创建矩阵
    Matrix *A = create_matrix(3, 3);
    A->data[0][0] = 2; A->data[0][1] = 3; A->data[0][2] = 1;
    A->data[1][0] = 4; A->data[1][1] = 1; A->data[1][2] = 2;
    A->data[2][0] = 6; A->data[2][1] = 2; A->data[2][2] = 5;
    
    printf("Original A:\n");
    print_matrix(A);
    
    // 计算逆矩阵
    Matrix *inv = matrix_inverse(A);
    if(inv) {
        printf("\nInverse of A (A⁻¹):\n");
        print_matrix(inv);
        
        // 验证：A × A⁻¹ = I
        Matrix *AAinv = mat_mul(A, inv);
        printf("\nA × A⁻¹:\n");
        print_matrix(AAinv);
        
        // 验证：A⁻¹ × A = I
        Matrix *AinvA = mat_mul(inv, A);
        printf("\nA⁻¹ × A:\n");
        print_matrix(AinvA);
        
        // 计算误差
        Matrix *I = create_identity(3);
        double error = 0.0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                error += fabs(AAinv->data[i][j] - I->data[i][j]);
            }
        }
        printf("\nReconstruction error: %.2e\n", error);
        
        free_matrix(AAinv);
        free_matrix(AinvA);
        free_matrix(I);
    }
    
    free_matrix(A);
    free_matrix(inv);
    
    // 测试2：奇异矩阵
    printf("\n=== Test: Singular Matrix ===\n");
    Matrix *B = create_matrix(2, 2);
    B->data[0][0] = 1; B->data[0][1] = 2;
    B->data[1][0] = 2; B->data[1][1] = 4;
    
    Matrix *invB = matrix_inverse(B);
    if(!invB) {
        printf("Correctly detected singular matrix!\n");
    }
    
    free_matrix(B);
    free_matrix(invB);
    
    return 0;
}