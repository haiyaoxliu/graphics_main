/*

    work 2: draw some lines

*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "lines.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    int *bits = (int*)calloc(512, sizeof(int));
    int depth = 2;


    //draw(0,8191,depth,bits);
    //draw(127,8064,depth,bits);
    //draw(16383,8192,depth,bits);
    //draw(16256,8319,depth,bits);

    for(int i = 0; i < 1; i++) {
        draw(rand()%64,rand()%64,depth,bits);
    }

    save(depth,bits);

    free(bits);
}

void draw(int p1, int p2, int depth, int *bits) {
    int t = 2 << depth;
    printf("draw from (%d,%d) to (%d,%d)\n", p1 % t, p1/t, p2 % t, p2/t);
    line(p1 % t, p1/t, p2 % t, p2/t, t, bits);
}


void line(int x0, int y0, int x1, int y1, int size, int *bits) {
    /*
    m = abs(slope) -w.r.t x
    f(x,y) = Ax+By+C
        A = dy, B = -dx, C = kdx;
        all values will be doubled to avoid division
        note: this function creates parallel lines for f(x,y) = k

    original error check:
    (0) D = 2A + B;
    (1) if D > 0: D += 2A - 2B
    (2) if D <=0: D += 2B;

    we know that inside quadrant 1 there're only 3 possible cases,
    so incrementing both x and y based on the value of the slope
    compared to the values 0,1/2,2,inf is ok

    generalized method:

        transform line into quadrant 1, so 0 < m < inf:

        initial error:
            0 < m < 1: f(x+1,y)-f(x,y) = -dx
            0 < 1/m < 1: f(x,y+1)-f(x,y) = dy

        error accumulation:
            use the fact that f(x,y) gives the same value along parallel lines
            to identify the slope
            m > 1/2 || f(x+2, y+1) - f(x,y) > 0 (current point closer to line)
                D = D + 2dy;
            1/m > 1/2 || f(x+1,y+2) - f(x,y) < 0 (current point farther from line)
                D = D - 2dx;

        incrementing:
            0 < m < 2: inc(x);
            0 < 1/m < 2: inc(y);
    */

    //find values for slope and orient into quadrant 1, include (t)wo * versions for convenience
    int dx, dy, tx, ty, xinc, yinc;
    tx = (dx = (xinc = x0<x1 ? 1 : -1) * (x1-x0)) << 1;
    ty = (dy = (yinc = y0<y1 ? 1 : -1) * (y1-y0)) << 1;

    int D = (dx>dy ? -dx : dy), T;

    while(1) {

        //plot current point
        set(bits, x0 + y0*size);

        //drawn entire line >>> quit
        if (x0 == x1 && y0 == y1) break;

        //error accumulation
        T = D;
        if (T < tx) { D += ty; x0 += xinc; }
        if (T > -ty) { D -= tx; y0 += yinc; }

    }
}

int adf(int a, int b) {
    return (a-b) * (((a-b)>0)-((a-b)<0));
}

void swap(int *x, int *y) {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

int half(int n) {
    return (n % 2) ? (n + 1)/2 : n/2;
}

void set(int bits[], int n) {
    bits[n/32] |= 1 << (n%32);
}

int get(int bits[], int n) {
    return ((bits[n/32] & (1 << (n%32) )));
}

void fprint(FILE *pic, int depth, int *bits) {
    int c = 255;
    int r = rand()%256;
    int g = rand()%256;
    int b = rand()%256;
    for(int i = 0; i < (4 << (2*depth)); i++) {

        if(i % (2 << depth) == 0) {
            fprintf(pic, "\n");
        }

        (get(bits,i)) ? fprintf(pic, "%d %d %d ",r,g,b) : fprintf(pic, "%d %d %d ",c,c,c);
    }
    fprintf(pic, "\n");
}

void save(int depth, int *bits) {
    FILE *pic;
    int size = 2<<depth;
    pic = fopen("lines.ppm", "w");

    fprintf(pic, "P3\n%d %d\n255",size,size);
    fprint(pic, depth, bits);

    fclose(pic);
}
