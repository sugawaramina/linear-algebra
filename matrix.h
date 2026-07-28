// matrix.h


#include <stdio.h>
#include <time.h>
typedef struct {
    int rows;
    int cols;
    double **data;  
} Matrix;           //基础矩阵

typedef struct {
    Matrix *A;      
    Matrix *b;      
    int n;          
} AugmentedMatrix;// 增广矩阵


Matrix* create_matrix(int rows, int cols);      // 分配内存，初始化为0
void free_matrix(Matrix *mat);                      // 释放每一行和整体
Matrix* copy_matrix(Matrix *src);                  // 深拷贝
void print_matrix(Matrix *mat);                    // 格式化打印


Matrix* mat_add(Matrix *a, Matrix *b);        // 矩阵加法
Matrix* mat_sub(Matrix *a, Matrix *b);        // 减法
Matrix* mat_mul(Matrix *a, Matrix *b);        // 乘法（注意行列匹配）
Matrix* mat_scalar_mul(Matrix *a, double k);  // 数乘
Matrix* mat_transpose(Matrix *a);             // 转置
Matrix* create_identity(int n);   // n×n 单位矩阵，对角线为1
Matrix* create_zero(int rows, int cols);  // 全零矩阵（其实 create_matrix 已实现）
Matrix* create_random(int rows, int cols); // 随机矩阵（方便测试）
double mat_trace(Matrix *a);  // 迹（trace）函数，返回矩阵的迹
int lu_decomposition(Matrix *A, Matrix **L, Matrix **U);

// 高斯消元（返回解向量，成功返回1，失败返回0）
//输入(参数)为矩阵A,向量b和空矩阵x(所以是二阶指针)，输出(参数)为解向量x
int gaussian_elimination(Matrix *A, Matrix *b, Matrix **x);

// 辅助函数
// 行交换
void swap_rows(Matrix *mat, int row1, int row2);

// 行缩放
void scale_row(Matrix *mat, int row, double factor);

// 行加减（row1 = row1 + factor * row2）
void add_scaled_row(Matrix *mat, int row1, int row2, double factor);

//矩阵转置
Matrix* matrix_inverse(Matrix *A);