/*

    work 2: draw some lines

*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "lines.h"

int depth = 4;

void subTriangle(int n, int x1, int y1, int x2, int y2, int x3, int y3, int size, int *bits)
{
  //Draw the 3 sides as black lines
  line(x1, y1, x2, y2, size, bits);
  line(x1, y1, x3, y3, size, bits);
  line(x2, y2, x3, y3, size, bits);

  //Calls itself 3 times with new corners, but only if the current number of recursions is smaller than the maximum depth
  if(n < depth)
  {
    //Smaller triangle 1
    subTriangle
    (
      n+1, //Number of recursions for the next call increased with 1
      (x1 + x2) / 2 + (x2 - x3) / 2, //x coordinate of first corner
      (y1 + y2) / 2 + (y2 - y3) / 2, //y coordinate of first corner
      (x1 + x2) / 2 + (x1 - x3) / 2, //x coordinate of second corner
      (y1 + y2) / 2 + (y1 - y3) / 2, //y coordinate of second corner
      (x1 + x2) / 2, //x coordinate of third corner
      (y1 + y2) / 2, //y coordinate of third corner
      size,
      bits
    );
    //Smaller triangle 2
    subTriangle
    (
      n+1, //Number of recursions for the next call increased with 1
      (x3 + x2) / 2 + (x2 - x1) / 2, //x coordinate of first corner
      (y3 + y2) / 2 + (y2 - y1) / 2, //y coordinate of first corner
      (x3 + x2) / 2 + (x3 - x1) / 2, //x coordinate of second corner
      (y3 + y2) / 2 + (y3 - y1) / 2, //y coordinate of second corner
      (x3 + x2) / 2, //x coordinate of third corner
      (y3 + y2) / 2,  //y coordinate of third corner
      size,
      bits
    );
    //Smaller triangle 3
    subTriangle
    (
      n+1, //Number of recursions for the next call increased with 1
      (x1 + x3) / 2 + (x3 - x2) / 2, //x coordinate of first corner
      (y1 + y3) / 2 + (y3 - y2) / 2, //y coordinate of first corner
      (x1 + x3) / 2 + (x1 - x2) / 2, //x coordinate of second corner
      (y1 + y3) / 2 + (y1 - y2) / 2, //y coordinate of second corner
      (x1 + x3) / 2, //x coordinate of third corner
      (y1 + y3) / 2,  //y coordinate of third corner
      size,
      bits
    );
  }
}


void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3, int size, int *bits) {
    //Draw the 3 sides of the triangle as black lines
    line(x1, y1, x2, y2, size, bits);
    line(x1, y1, x3, y3, size, bits);
    line(x2, y2, x3, y3, size, bits);

    //Call the recursive function that'll draw all the rest. The 3 corners of it are always the centers of sides, so they're averages
    subTriangle
    (
      1, //This represents the first recursion
      (x1 + x2) / 2, //x coordinate of first corner
      (y1 + y2) / 2, //y coordinate of first corner
      (x1 + x3) / 2, //x coordinate of second corner
      (y1 + y3) / 2, //y coordinate of second corner
      (x2 + x3) / 2, //x coordinate of third corner
      (y2 + y3) / 2,  //y coordinate of third corner
      size,
      bits
    );
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int *bits = (int*)calloc(512, sizeof(int));
    int depth = 6;


    //draw(0,8191,depth,bits);
    //draw(127,8064,depth,bits);
    //draw(16383,8192,depth,bits);
    //draw(16256,8319,depth,bits);

    /*for(int i = 0; i < 1; i++) {
        draw(rand()%64,rand()%64,depth,bits);
    }*/

    sierpinski(0,0,127,0,0,127,2 << depth, bits);

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

    //find values for slope and orient into quadrant 1
    int dx, dy, tx, ty, xinc, yinc, D, T;
    tx = (dx = (xinc = x0<x1 ? 1 : -1) * (x1-x0)) << 1;
    ty = (dy = (yinc = y0<y1 ? 1 : -1) * (y1-y0)) << 1;

    //init error
    D = (dx>dy ? -dx : dy);

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
