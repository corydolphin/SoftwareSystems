/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    double **data;
    int rows, cols;
} Matrix;


// Makes a new matrix and sets all elements to zero.
Matrix *make_matrix(int rows, int cols) {
    int i;
    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->data = malloc(rows * sizeof(double *));
    matrix->rows = rows;
    matrix->cols = cols;

    for (i=0; i<rows; i++) {
	// use calloc to initialize to 0
	matrix->data[i] = calloc(cols, sizeof(double));
    }
    return matrix;
}

// Prints the elements of a matrix.
void print_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    printf("%lf ", matrix->data[i][j]);
	}
	printf("\n");
    }
}

// Adds a scalar to all elements of a matrix.
void increment_matrix(Matrix *matrix, int incr) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] += incr;
	}
    }
}

// Sets the elements of a matrix to consecutive numbers.
void consecutive_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] = i * matrix->cols + j;
	}
    }
}

// Adds two matrices elementwise and stores the result in the given
// destination matrix (C).
void add_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j;

    assert(A->rows == B->rows && B->rows == C->rows);
    assert(A->cols == B->cols && B->cols == C->cols);

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    C->data[i][j] =  A->data[i][j] + B->data[i][j];
	}
    }
}

// Adds two matrices elementwise and returns a new matrix.
Matrix *add_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, A->cols);
    add_matrix(A, B, C);
    return C;
}

// Performs matrix multiplication and stores the result in the given
// destination matrix (C).
void mult_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j, k;

    assert(A->rows == B->cols);
    assert(A->rows == C->rows);
    assert(B->cols == C->cols);

    for (i=0; i<C->rows; i++) {
	for (j=0; j<C->cols; j++) {
	    for (k=0; k<A->cols; k++) {
		C->data[i][j] += A->data[i][k] * B->data[k][j];
	    }
	}
    }
}

// Performs matrix multiplication and returns a new matrix.
Matrix *mult_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, B->cols);
    mult_matrix(A, B, C);
    return C;
}

double matrix_sum1(Matrix *A) {
    double total = 0.0;
    int i, j;
    /*
    Assuming that the matrix is bigger than the memory cache and that a memory 
    cache line is big enough to hold 8 matrix elements, what cache hit rate
    would you expect foreach version of matrix_sum? Explain your reasoning.


    
    Assuming that the cache line is big enough to hold 8 matrix elements, and
    assuming that the matrix has at leaast 8 elements per row, and is not arranged
    such that rows are sequentially allocated in memory:
    I expect that this function will hit cache 7/8ths of the time. As this function
    accesses a row, and then iterates through the columns in the row, request for
    the first index in a new array will cache the next 8 element, resulting in
    7 cache hits for one cache miss.

    */
    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
    
double matrix_sum2(Matrix *A) {
    /*
    Assuming that the cache line is big enough to hold 8 matrix elements, and
    assuming that the matrix has at leaast 8 elements per row, and is not arranged
    such that rows are sequentially allocated in memory:

    I expect that this function will never hit cache. Each request to a different
    row will trigger a caching of the next 8 elements of the row, but the next
    iteration of the function will request a new row, blowing away the cache.

    If the rows are allocated sequentially, and the there are less than 8 columns,
    the situation is quite different, as accessing an element in a row may trigger
    the caching of elements of the next row. This is unlikely, thus this excercise
    is left up to the reader.
    */


    double total = 0.0;
    int i, j;

    for (j=0; j<A->cols; j++) {
	for (i=0; i<A->rows; i++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
    

// Adds up the rows of A and returns a heap-allocated array of doubles.
double *row_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->rows * sizeof(double));

    for (i=0; i<A->rows; i++) {
	total = 0.0;
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
	res[i] = total;
    }
    return res;
}

// Adds up the cols of A and returns a heap-allocated array of doubles.
double *col_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->cols * sizeof(double));


    for (j=0; j<A->cols; j++) {
    total = 0.0;
    for (i=0; i<A->rows; i++) {
        total += A->data[i][j];
    }
    res[j] = total;
    }
    return res;
}

// Adds up the two diags of A and returns a heap allocated array of 2 doubles
double *diag_sum(Matrix *A) {
    double* total = malloc(2*sizeof(double));
    int i;

    total[0] = 0.0;
    total[1] = 0.0;

    int max = A->cols - 1;
    for (i=0; i<A->cols; i++) {
        total[0] += A->data[i][i];
        total[1] += A->data[max - i][max - i];
    }


    return total;
}


/* 
   http://en.wikipedia.org/wiki/Magic_square

   A magic square is an arrangement of numbers (usually integers) in a
   square grid, where the numbers in each row, and in each column, and
   the numbers in the forward and backward main diagonals, all add up
   to the same number. 

   Write a function called is_magic_square() that takes a matrix and 
   returns an int, 1 if the matrix is a magic square, and 0 otherwise.

   Feel free to use row_sum().
*/


int is_magic_square(Matrix *mat){
    int i;

    if(mat->cols != mat->rows){
        return 0; // must be a square
    }

    double *r_sum = row_sum(mat);
    double *c_sum = col_sum(mat);
    double *d_sum = diag_sum(mat);

    for(i =0; i < mat->rows; i++){
        if(r_sum[i] != c_sum[i] || 
           r_sum[i] != d_sum[0] ||
           c_sum[i] != d_sum[1]){
            return 0;
        }
    }

    return 1;
}

// Example magic square from Wiki
// http://en.wikipedia.org/wiki/Magic_square
Matrix *get_magic_example(){

    Matrix *mat = make_matrix(3,3);

    mat->data[0][0] = 2.0;
    mat->data[0][1] = 7.0;
    mat->data[0][2] = 6.0;

    mat->data[1][0] = 9.0;
    mat->data[1][1] = 5.0;
    mat->data[1][2] = 1.0;

    mat->data[2][0] = 4.0;
    mat->data[2][1] = 3.0;
    mat->data[2][2] = 8.0;

    return mat;
}

int main() {
    int i;

    Matrix *A = make_matrix(3, 4);
    consecutive_matrix(A);
    printf("A\n");
    print_matrix(A);

    Matrix *C = add_matrix_func(A, A);
    printf("A + A\n");
    print_matrix(C);

    Matrix *B = make_matrix(4, 3);
    increment_matrix(B, 1);
    printf("B\n");
    print_matrix(B);

    Matrix *D = mult_matrix_func(A, B);
    printf("D\n");
    print_matrix(D);

    double sum = matrix_sum1(A);
    printf("sum = %lf\n", sum);

    sum = matrix_sum2(A);
    printf("sum = %lf\n", sum);

    double *sums = row_sum(A);
    for (i=0; i<A->rows; i++) {
	printf("row %d\t%lf\n", i, sums[i]);
    }
    // should print 6, 22, 38


    Matrix *mag = get_magic_example();
    printf("%f\n", diag_sum(mag)[0]);
    assert(is_magic_square(mag));
    printf("You got yo self a magik skware\n");
    return 0;
}
