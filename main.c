#include "matrix.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // 测试1：直线拟合 y = 2x + 3
    printf("=== Test 1: Linear Regression ===\n");
    printf("Fit y = a*x + b to data points:\n");
    
    // 数据点 (x, y)
    double points[][2] = {
        {1.0, 5.0},   // 2*1 + 3 = 5
        {2.0, 7.0},   // 2*2 + 3 = 7
        {3.0, 9.0},   // 2*3 + 3 = 9
        {4.0, 11.0},  // 2*4 + 3 = 11
        {5.0, 13.0}   // 2*5 + 3 = 13
    };
    int n_points = 5;
    
    // 设计矩阵 A: 每行是 [x, 1]
    Matrix *A = create_matrix(n_points, 2);
    Matrix *b = create_matrix(n_points, 1);
    
    for(int i = 0; i < n_points; i++) {
        A->data[i][0] = points[i][0];  // x
        A->data[i][1] = 1.0;            // 常数项
        b->data[i][0] = points[i][1];   // y
    }
    
    printf("Data points:\n");
    for(int i = 0; i < n_points; i++) {
        printf("  (%.1f, %.1f)\n", points[i][0], points[i][1]);
    }
    
    Matrix *x = NULL;
    if(least_squares(A, b, &x)) {
        printf("\nFitted coefficients:\n");
        printf("  a = %.4f (slope)\n", x->data[0][0]);
        printf("  b = %.4f (intercept)\n", x->data[1][0]);
        
        // 计算残差
        Matrix *Ax = mat_mul(A, x);
        Matrix *residual = mat_sub(b, Ax);
        double error = 0.0;
        for(int i = 0; i < residual->rows; i++) {
            error += residual->data[i][0] * residual->data[i][0];
        }
        printf("  Residual norm squared: %.4e\n", error);
        
        free_matrix(Ax);
        free_matrix(residual);
    }
    
    free_matrix(A);
    free_matrix(b);
    free_matrix(x);
    
    // 测试2：二次拟合
    printf("\n=== Test 2: Quadratic Regression ===\n");
    printf("Fit y = a*x² + b*x + c\n");
    
    // 二次函数 y = x² + 2x + 1
    double points2[][2] = {
        {0.0, 1.0},
        {1.0, 4.0},
        {2.0, 9.0},
        {3.0, 16.0},
        {4.0, 25.0}
    };
    
    Matrix *A2 = create_matrix(5, 3);
    Matrix *b2 = create_matrix(5, 1);
    
    for(int i = 0; i < 5; i++) {
        double x_val = points2[i][0];
        A2->data[i][0] = x_val * x_val;  // x²
        A2->data[i][1] = x_val;           // x
        A2->data[i][2] = 1.0;             // 常数
        b2->data[i][0] = points2[i][1];
    }
    
    Matrix *x2 = NULL;
    if(least_squares(A2, b2, &x2)) {
        printf("Fitted coefficients:\n");
        printf("  a = %.4f (x² coefficient)\n", x2->data[0][0]);
        printf("  b = %.4f (x coefficient)\n", x2->data[1][0]);
        printf("  c = %.4f (constant)\n", x2->data[2][0]);
        
        // 验证：应该接近 a=1, b=2, c=1
        Matrix *Ax2 = mat_mul(A2, x2);
        Matrix *residual2 = mat_sub(b2, Ax2);
        double error2 = 0.0;
        for(int i = 0; i < residual2->rows; i++) {
            error2 += residual2->data[i][0] * residual2->data[i][0];
        }
        printf("  Residual norm squared: %.4e\n", error2);
        
        free_matrix(Ax2);
        free_matrix(residual2);
    }
    
    free_matrix(A2);
    free_matrix(b2);
    free_matrix(x2);
    
    // 测试3：噪声数据拟合
    printf("\n=== Test 3: Noisy Data ===\n");
    Matrix *A3 = create_matrix(10, 2);
    Matrix *b3 = create_matrix(10, 1);
    
    // 真实函数: y = 2.5x + 1.3，加噪声
    for(int i = 0; i < 10; i++) {
        double x_val = i * 0.5;
        A3->data[i][0] = x_val;
        A3->data[i][1] = 1.0;
        // y = 2.5*x + 1.3 + 噪声
        double noise = ((rand() % 100) / 100.0 - 0.5) * 0.5; // [-0.25, 0.25]
        b3->data[i][0] = 2.5 * x_val + 1.3 + noise;
        printf("  (%.1f, %.3f)\n", x_val, b3->data[i][0]);
    }
    
    Matrix *x3 = NULL;
    if(least_squares(A3, b3, &x3)) {
        printf("\nFitted coefficients:\n");
        printf("  slope = %.4f (expected 2.5)\n", x3->data[0][0]);
        printf("  intercept = %.4f (expected 1.3)\n", x3->data[1][0]);
    }
    
    free_matrix(A3);
    free_matrix(b3);
    free_matrix(x3);
    
    return 0;
}