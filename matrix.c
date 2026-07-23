#include "matrix.h"
#include <stdlib.h>

void free_matrix(Matrix *mat){
    if(!mat) return;
    for(int i = 0; i < mat->rows; i++){
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

Matrix* create_matrix(int rows, int cols){
    

    if(rows <= 0 || cols <= 0){
        return NULL; // 无效的行列数
    }
  

    Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double**)malloc(rows * sizeof(double*));
    if(!mat->data){
        free(mat);
        return NULL; // 内存分配失败
    }
  for(int i = 0; i < rows; i++){
        mat->data[i] = (double*)calloc(cols, sizeof(double)); // 初始化为0
        if(!mat->data[i]){
            for(int j = 0; j < i; j++){
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL; // 内存分配失败
        }
    }
    return mat;
}

Matrix* copy_matrix(Matrix *src){
    Matrix *copy = create_matrix(src->rows, src->cols);
    for(int i = 0; i < src->rows; i++){
        for(int j = 0; j < src->cols; j++){
            copy->data[i][j] = src->data[i][j];
        }
    }
    return copy;
}


void print_matrix(Matrix *mat){
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            printf("%8.3f ", mat->data[i][j]);  
        }
        printf("\n");
    }
}


Matrix* mat_add(Matrix *a, Matrix *b){
    if(!a || !b){
        return NULL; // 空指针检查
    }

    if(a->rows != b->rows || a->cols != b->cols){
        return NULL; // 行列不匹配
    }
    Matrix *result = create_matrix(a->rows, a->cols);
    for(int i = 0; i < a->rows; i++){
        for(int j = 0; j < a->cols; j++){
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}

Matrix* mat_sub(Matrix *a, Matrix *b){
    if(!a || !b){
        return NULL; // 空指针检查
    }

    if(a->rows != b->rows || a->cols != b->cols){
        return NULL; // 行列不匹配
    }
    Matrix *result = create_matrix(a->rows, a->cols);
    for(int i = 0; i < a->rows; i++){
        for(int j = 0; j < a->cols; j++){
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    return result;
}



Matrix* mat_mul(Matrix *a, Matrix *b){
    if(!a || !b){
        return NULL; // 空指针检查
    }

    if(a->cols != b->rows){
        return NULL; // 行列不匹配
    }

    Matrix *result = create_matrix(a->rows, b->cols);
    for(int i = 0; i < a->rows; i++){
        for(int j = 0; j < b->cols; j++){
            for(int k = 0; k < a->cols; k++){
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}

Matrix* mat_scalar_mul(Matrix *a, double k){
    if(!a){
        return NULL; // 空指针检查
    }
    Matrix *result = create_matrix(a->rows, a->cols);
    for(int i = 0; i < a->rows; i++){
        for(int j = 0; j < a->cols; j++){
            result->data[i][j] = a->data[i][j] * k;
        }
    }
    return result;
}

Matrix* mat_transpose(Matrix *a){
    if(!a){
        return NULL; // 空指针检查
    }
    Matrix *result = create_matrix(a->cols, a->rows);
    for(int i = 0; i < a->rows; i++){
        for(int j = 0; j < a->cols; j++){
            result->data[j][i] = a->data[i][j];
        }
    }
    return result;
}\

Matrix* create_identity(int n){
    if(n <= 0){
        return NULL; // 无效的大小
    }

    Matrix *mat = create_matrix(n, n);
    if(!mat){
        return NULL; // 内存分配失败
    }
    
    for(int i = 0; i < n; i++){
        mat->data[i][i] = 1.0;
    }
    return mat;
}

Matrix* create_zero(int rows, int cols){
    if(rows <= 0 || cols <= 0){
        return NULL; // 无效的行列数
    }
  

    Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double**)malloc(rows * sizeof(double*));
    if(!mat->data){
        free(mat);
        return NULL; // 内存分配失败
    }
  for(int i = 0; i < rows; i++){
        mat->data[i] = (double*)calloc(cols, sizeof(double)); // 初始化为0
        if(!mat->data[i]){
            for(int j = 0; j < i; j++){
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL; // 内存分配失败
        }
    }
    return mat;
}

Matrix* create_random(int rows, int cols){
    if(rows <= 0 || cols <= 0){
        return NULL; // 无效的行列数
    }
  
    Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double**)malloc(rows * sizeof(double*));
    if(!mat->data){
        free(mat);
        return NULL; // 内存分配失败
    }
  for(int i = 0; i < rows; i++){
        mat->data[i] = (double*)malloc(cols * sizeof(double));
        if(!mat->data[i]){
            for(int j = 0; j < i; j++){
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL; // 内存分配失败
        }

        static int seeded = 0;
        if(!seeded){
            srand((unsigned int)time(NULL)); // 仅在第一次调用时进行随机数种子初始化
            seeded = 1;
        }
        for(int j = 0; j < cols; j++){
           mat->data[i][j] = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        }
    }
    return mat;
}

double mat_trace(Matrix *a){
    if(!a || a->rows != a->cols){
        return 0; // 空指针检查或非方阵
    }
    double trace = 0;
    for(int i = 0; i < a->rows; i++){
        trace += a->data[i][i];
    }
    return trace;
}