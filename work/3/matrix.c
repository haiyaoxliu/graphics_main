#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m
Returns:

print the matrix
*/
void print_matrix(struct matrix *d) {
    int i, j;
    //printf("%d, %d, ?%d\n\n", d->rows, d->cols, d->lastcol);
    for(i = 0; i < d->rows; i++) {
        for(j = 0; j < d->lastcol; j++) {
            printf("%0.2f\t", d->m[i][j]);
        }
        printf("\n");
    }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns:

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
    int i, j;
    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            m->m[i][j] = (i == j);
        }
    }
    m->lastcol = m->cols;
}

/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
    int i, j, k;
    double t[b->rows]; //aux col

    //a->lastcol should equal b->rows
    for(i = 0; i < b->lastcol; i++) {
        for(j = 0; j < b->rows; j++) {
            t[j] = b->m[j][i];
            b->m[j][i] = 0;
            for(k = 0; k < a->rows; k++) {
                b->m[j][i] += t[j]*a->m[k][j];
            }
        }
    }
}



/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols
Returns:

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
  }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols
Returns:

Reallocates the memory for m->m such that it now has
newcols number of columns
====================*/
void grow_matrix(struct matrix *m, int newcols) {

  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}

/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++)
    for (c=0; c < a->cols; c++)
      b->m[r][c] = a->m[r][c];
}
