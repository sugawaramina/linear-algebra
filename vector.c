#include "vector.h"
#include <stdlib.h>
#include <math.h>




Matrix* create_vector(int n){
    if(n <= 0){
        return NULL; // 无效的维度
    }
  
    Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = n;
    mat->cols = 1;
    mat->data = (double**)malloc(n * sizeof(double*));
    if(!mat->data){
        free(mat);
        return NULL; // 内存分配失败
    }

    
  for(int i = 0; i < n; i++){
        mat->data[i] = (double*)calloc(1, sizeof(double)); // 初始化为0
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

double vector_norm(Matrix *v){
    if(!v || v->cols != 1){
        return -1; // 空指针检查或非列向量
    }
    double sum = 0.0;
    for(int i = 0; i < v->rows; i++){
        sum += v->data[i][0] * v->data[i][0];
    }
    return sqrt(sum);
}

double vector_dot(Matrix *a, Matrix *b){
    if(!a || !b || a->cols != 1 || b->cols != 1 || a->rows != b->rows){
        return -1; 
    }

    double sum = 0.0;

    for(int i = 0; i < a->rows; i++){
        sum += a->data[i][0] * b->data[i][0];
    }

    return sum;
}

Matrix* vector_scalar_mul(Matrix *v, double k){

    if(!v || v->cols != 1){
        return NULL; 
    }

    Matrix *result = create_vector(v->rows);

    for(int i = 0; i < v->rows; i++){
        result->data[i][0] = v->data[i][0] * k;
    }

    return result;
}

Matrix* vector_sub(Matrix *a, Matrix *b){
    if(!a || !b || a->cols != 1 || b->cols != 1 || a->rows != b->rows){
        return NULL; 
    }

    Matrix *result = create_vector(a->rows);

    for(int i = 0; i < a->rows; i++){
        result->data[i][0] = a->data[i][0] - b->data[i][0];
    }

    return result;
}

Matrix* get_column(Matrix *A, int col){
    if(!A || col < 0 || col >= A->cols){
        return NULL; // 空指针检查或列索引越界
    }

    Matrix *result = create_vector(A->rows);
    for(int i = 0; i < A->rows; i++){
        result->data[i][0] = A->data[i][col];
    }
    return result;
}



int qr_decomposition(Matrix *A, Matrix **Q, Matrix **R){
    if(!A || !Q || !R || A->rows < A->cols){
        return 0; // 空指针检查或行数小于列数
    }

    int m = A->rows;
    int n = A->cols;

    *Q = create_matrix(m, n);
    *R = create_matrix(n, n);

    for(int j = 0; j < n; j++){
        Matrix *v = get_column(A, j);
        for(int i = 0; i < j; i++){
            double r_ij = vector_dot(get_column(*Q, i), v);
            (*R)->data[i][j] = r_ij;
            Matrix *scaled_qi = vector_scalar_mul(get_column(*Q, i), r_ij);
            Matrix *temp_v = vector_sub(v, scaled_qi);

            free_matrix(v);
            free_matrix(scaled_qi);
            v = temp_v;
        }

        double r_jj = vector_norm(v);

        (*R)->data[j][j] = r_jj;

        for(int i = 0; i < m; i++){
            (*Q)->data[i][j] = v->data[i][0] / r_jj;
        }

        free_matrix(v);
    }
    return 1;
}

int least_squares(Matrix *A, Matrix *b, Matrix **x){
    if(!A || !b || !x || A->rows != b->rows){
        return 0; // 空指针检查或行数不匹配
    }

    Matrix *Q = NULL, *R = NULL;
    if(!qr_decomposition(A, &Q, &R)){
        return 0; // QR分解失败
    }

    Matrix *Qt_b = mat_mul(mat_transpose(Q), b);
    if(!Qt_b){
        free_matrix(Q);
        free_matrix(R);
        return 0; // 矩阵乘法失败
    }

    Matrix *y = create_matrix(R->rows, 1);
    if(!y){
        free_matrix(Q);
        free_matrix(R);
        free_matrix(Qt_b);
        return 0; // 内存分配失败
    }
    for(int i = 0; i < R->rows; i++){
        y->data[i][0] = Qt_b->data[i][0];
    }

    *x = create_matrix(R->cols, 1);
    if(!(*x)){
        free_matrix(Q);
        free_matrix(R);
        free_matrix(Qt_b);
        free_matrix(y);
        return 0; // 内存分配失败
    }

    int n = R->rows;
    for(int i = n - 1; i >= 0; i--){
        double sum = y->data[i][0];
        for(int j = i + 1; j < n; j++){
            sum -= R->data[i][j] * (*x)->data[j][0];
        }
        if(fabs(R->data[i][i]) < 1e-12){
            free_matrix(Q);
            free_matrix(R);
            free_matrix(Qt_b);
            free_matrix(y);
            free_matrix(*x);
            *x = NULL;
            return 0; // 上三角矩阵奇异或病态
        }
        (*x)->data[i][0] = sum / R->data[i][i];
    }

    free_matrix(Q);
    free_matrix(R);
    free_matrix(Qt_b);
    free_matrix(y);

    return 1;
}