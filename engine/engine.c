/*
    graphics engine:
    current functionality:
        plot points
        draw lines
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "engine.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    int depth = 6;
    int length = 1 << depth;
    int size = 1 << (depth << 1);
    unsigned char *colors = (unsigned char *)calloc(size*3*sizeof(unsigned char));



    //draw(0,8191,depth,bits);
    //draw(127,8064,depth,bits);
    //draw(16383,8192,depth,bits);
    //draw(16256,8319,depth,bits);
    //1 4 16 64 ... 2^2n size
    //1 2 4 8   ... 2^n len
    //1 2 3 4   ... n
    //unsigned char **bits = (unsigned char **)calloc(size * 3, sizeof(unsigned char));
    int r = rand()%16384;
    for(int i = 0; i < 10; i++) {
        draw(r,rand()%16384,depth,bits);
    }

    save(depth,bits);

    free(colors);
}

void draw(int p1, int p2, int depth, unsigned char *colors) {
    int t = 2 << depth;
    printf("draw from (%d,%d) to (%d,%d)\n", p1 % t, p1/t, p2 % t, p2/t);
    line(p1 % t, p1/t, p2 % t, p2/t, t, bits);
}


void line(int x0, int y0, int x1, int y1, int size, unsigned char *colors) {

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

void set(int bits[], int n) {
    bits[n/32] |= 1 << (n%32);
}

int get(int bits[], int n) {
    return ((bits[n/32] & (1 << (n%32) )));
}

void fprint(FILE *pic, int depth, unsigned char *colors) {
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

void save(int depth, unsigned char *colors) {
    FILE *pic;
    int size = 2<<depth;
    pic = fopen("engine.ppm", "w");

    fprintf(pic, "P3\n%d %d\n255",size,size);
    fprint(pic, depth, bits);

    fclose(pic);
}
