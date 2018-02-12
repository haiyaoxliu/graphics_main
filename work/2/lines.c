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
    int depth = 6;


    //draw(0,8191,depth,bits);
    //draw(127,8064,depth,bits);
    //draw(16383,8192,depth,bits);
    //draw(16256,8319,depth,bits);

    for(int i = 0; i < 10; i++) {
        draw(rand()%16384,rand()%16384,depth,bits);
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
    //positive differences
    int dx = (x1-x0) * (((x1-x0)>0)-((x1-x0)<0));
    int dy = (y1-y0) * (((y1-y0)>0)-((y1-y0)<0));

    //which direction to increment in
    int xinc = x0<x1 ? 1 : -1;
    int yinc = y0<y1 ? 1 : -1;

    //
    int err = (dx>dy ? dx : -dy)/2, e2;
    while(1) {
        //plot current point
        set(bits,x0+y0*size);

        //drawn entire line >>> quit
        if (x0 == x1 && y0 == y1) break;

        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += xinc; }
        if (e2 < dy) { err += dx; y0 += yinc; }
    }
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
    for(int i = 0; i < (4 << (2*depth)); i++) {

        if(i % (2 << depth) == 0) {
            fprintf(pic, "\n");
        }

        int c = 255;
        int r = rand()%256;
        int g = rand()%256;
        int b = rand()%256;
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
