// matrix.h


#include <stdio.h>
#include <time.h>
typedef struct {
    int rows;
    int cols;
    double **data;  
} Matrix;

// 必须实现的第一个函数（请你自己写）：
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