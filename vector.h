#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"




//QR分解
int qr_decomposition(Matrix *A, Matrix **Q, Matrix **R);

//最小二乘法求解Ax=b
int least_squares(Matrix *A, Matrix *b, Matrix **x);

//基础函数

// 创建向量（n维列向量）
Matrix* create_vector(int n);

// 计算向量的范数（L2范数）
double vector_norm(Matrix *v);

// 计算向量的点积
double vector_dot(Matrix *a, Matrix *b); 

//向量数乘
Matrix* vector_scalar_mul(Matrix *v, double k); 

//向量减法
Matrix* vector_sub(Matrix *a, Matrix *b);  

//提取矩阵的某一列作为向量
Matrix* get_column(Matrix *A, int col);


#endif // VECTOR_H