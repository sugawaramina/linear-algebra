#include "matrix.h"
#include <math.h>
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

void swap_rows(Matrix *mat, int row1, int row2){
    if(!mat || row1 < 0 || row2 < 0 || row1 >= mat->rows || row2 >= mat->rows){
        return; // 空指针检查或行索引越界
    }
    double *temp = mat->data[row1];
    mat->data[row1] = mat->data[row2];
    mat->data[row2] = temp;
}

void scale_row(Matrix *mat, int row, double factor){
    if(!mat || row < 0 || row >= mat->rows){
        return; // 空指针检查或行索引越界
    }
    for(int j = 0; j < mat->cols; j++){
        mat->data[row][j] *= factor;
    }
}

void add_scaled_row(Matrix *mat, int row1, int row2, double factor){
    if(!mat || row1 < 0 || row2 < 0 || row1 >= mat->rows || row2 >= mat->rows){
        return; // 空指针检查或行索引越界
    }
    for(int j = 0; j < mat->cols; j++){
        mat->data[row1][j] += factor * mat->data[row2][j];
    }
}

int gaussian_elimination(Matrix *A, Matrix *b, Matrix **x){
    if(!A || !b || !x || A->rows != b->rows){
        return 0; // 空指针检查或行数不匹配
    }

    int n = A->rows;
    Matrix *aug = create_matrix(n, A->cols + 1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < A->cols; j++){
            aug->data[i][j] = A->data[i][j];
        }
        aug->data[i][A->cols] = b->data[i][0];
    }
    // 高斯消元过程
    for(int i = 0; i < n; i++){
        int max_row = i;
        for(int k = i + 1; k < n; k++){
            if(fabs(aug->data[k][i]) > fabs(aug->data[max_row][i])){
                max_row = k;
            }
        }
        swap_rows(aug, i, max_row);

        if(fabs(aug->data[i][i]) < 1e-10){
            free_matrix(aug);
            return 0; // 无解或无唯一解
        }

        for(int k = i + 1; k < n; k++){
            double factor = aug->data[k][i] / aug->data[i][i];
            add_scaled_row(aug, k, i, -factor);
        }
    }

    *x = create_matrix(n, 1);
    for(int i = n - 1; i >= 0; i--){
        (*x)->data[i][0] = aug->data[i][A->cols];
        for(int j = i + 1; j < A->cols; j++){
            (*x)->data[i][0] -= aug->data[i][j] * (*x)->data[j][0];
        }
        (*x)->data[i][0] /= aug->data[i][i];
    }

    free_matrix(aug);
    return 1;

}

int lu_decomposition(Matrix *A, Matrix **L, Matrix **U){
    if(!A || !L || !U || A->rows != A->cols){
        return 0; // 空指针检查或非方阵
    }

    int n = A->rows;
    *L = create_matrix(n, n);
    *U = copy_matrix(A);

    if(!(*L) || !(*U)){
        free_matrix(*L);
        free_matrix(*U);
        return 0; // 内存分配失败
    }

    for(int i = 0; i < n; i++){
        (*L)->data[i][i] = 1.0;
    }

    for(int col = 0; col < n; col++){
        if(fabs((*U)->data[col][col]) < 1e-10){
            free_matrix(*L);
            free_matrix(*U);
            return 0; // 矩阵奇异，无法分解
        }

        for(int row = col + 1; row < n; row++){
            double factor = (*U)->data[row][col] / (*U)->data[col][col];
            (*L)->data[row][col] = factor;
            add_scaled_row(*U, row, col, -factor);
        }
    }

    return 1;
}


//向前替换:解L * y = b
static int forward_substitution(Matrix *L, Matrix *b, Matrix **y){
    if(!L || !b || !y || L->rows != b->rows){
        return 0; // 空指针检查或行数不匹配
    }
    int n = L->rows;
    *y = create_matrix(n, 1);
    if(!(*y)){
        return 0; // 内存分配失败
    }

    
    for(int i = 0; i < n; i++){
        (*y)->data[i][0] = b->data[i][0];
        for(int j = 0; j < i; j++){
            (*y)->data[i][0] -= L->data[i][j] * (*y)->data[j][0];
        }
        (*y)->data[i][0] /= L->data[i][i];
    }
    return 1 ;
}


//向后替换:解U * x = y
static int backward_substitution(Matrix *U, Matrix *y, Matrix **x) {
    if(!U || !y || !x || U->rows != y->rows) {
        return 0; // 空指针检查或行数不匹配
    }
    int n = U->rows;
    *x = create_matrix(n, 1);

    if(!(*x)){
        return 0; // 内存分配失败
    }

    for(int i = n - 1; i >= 0; i--){
        (*x)->data[i][0] = y->data[i][0];
        for(int j = i + 1; j < n; j++){
            (*x)->data[i][0] -= U->data[i][j] * (*x)->data[j][0];
        }
        (*x)->data[i][0] /= U->data[i][i];
    }
    return 1;
}

Matrix* matrix_inverse(Matrix *A){
    if(!A || A->rows != A->cols){
        return NULL; // 空指针检查或非方阵
    }

    int n = A->rows;
    Matrix *L = NULL, *U = NULL;
    if(!lu_decomposition(A, &L, &U)){
        return NULL; // LU分解失败，矩阵可能是奇异的
    }

    Matrix *inv = create_matrix(n, n);
    if(!inv){
        free_matrix(L);
        free_matrix(U);
        return NULL; // 内存分配失败
    }

    for(int i = 0; i < n; i++){
        Matrix *e = create_matrix(n, 1);
        e->data[i][0] = 1.0;

        Matrix *y = NULL;
     
        if(!forward_substitution(L, e, &y)){
            free_matrix(e);
            free_matrix(inv);
            free_matrix(L);
            free_matrix(U);
            return NULL; // 前向替换失败
        }

        Matrix *x = NULL;
        if(!backward_substitution(U, y, &x)){
            free_matrix(e);
            free_matrix(y);
            free_matrix(inv);
            free_matrix(L);
            free_matrix(U);
            return NULL; // 回代失败
        }

        for(int j = 0; j < n; j++){
            inv->data[j][i] = x->data[j][0];
        }

        free_matrix(e);
        free_matrix(y);
        free_matrix(x);
    }

    free_matrix(L);
    free_matrix(U);

    return inv;
}