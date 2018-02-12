/*

    work 1: make a ppm

    sierpinski

    * * * * * * * * * * * * * * * *
    * _ * _ * _ * _ * _ * _ * _ * _
    * * _ _ * * _ _ * * _ _ * * _ _
    * _ _ _ * _ _ _ * _ _ _ * _ _ _
    * * * * _ _ _ _ * * * * _ _ _ _
    * _ * _ _ _ _ _ * _ * _ _ _ _ _
    * * _ _ _ _ _ _ * * _ _ _ _ _ _
    * _ _ _ _ _ _ _ * _ _ _ _ _ _ _
    * * * * * * * * _ _ _ _ _ _ _ _
    * _ * _ * _ * _ _ _ _ _ _ _ _ _
    * * _ _ * * _ _ _ _ _ _ _ _ _ _
    * _ _ _ * _ _ _ _ _ _ _ _ _ _ _
    * * * * _ _ _ _ _ _ _ _ _ _ _ _
    * _ * _ _ _ _ _ _ _ _ _ _ _ _ _
    * * _ _ _ _ _ _ _ _ _ _ _ _ _ _
    * _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "sierpinski.h"

int main(int argc, char **argv) {
    int *bits = (int*)calloc(512, sizeof(int));
    int depth = 6;

    create(depth,bits);
    save(depth,bits);

    free(bits);
}

void create(int depth, int *bits) {
    int t = 2 << depth;
    for(int row = 0; row < t; row++) {
        for(int col = 0; col < t; col++) {
            (col & row) ? set(bits, row*t+col) : 0;
        }
    }
}

/*
void create(int depth, int *bits) {
    if (depth < 0 || depth > 6) {
        perror("invalid depth");
        exit(1);
    }

    set(bits, 0);
    set(bits, 1);
    set(bits, 2 << depth);

    for(int d = 0; d < depth; d++) {
        for(int r = 0; r < (2 << d); r++) {
            for(int c = 0; c < (2 << d); c++) {
                int t = 2 << d;
                if(get(bits,c+r*(2<<depth))) {
                    set(bits,(t+c) + r*(2<<depth));
                    set(bits,c + (t+r)*(2<<depth));
                }
                else continue;
            }
        }
    }
}
*/

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

        int t = (i%(2<<depth)+(i/(2<<depth)))/2;
        int b = 255 - (i%(2<<depth)+(i/(2<<depth)));
        (get(bits,i)) ? fprintf(pic, "%d %d %d ",t,t,t) : fprintf(pic, "%d %d %d ",b,b,b);
    }
    fprintf(pic, "\n");
}

void save(int depth, int *bits) {
    FILE *pic;
    int size = 2<<depth;
    pic = fopen("sierpinski.ppm", "w");

    fprintf(pic, "P3\n%d %d\n255",size,size);
    fprint(pic, depth, bits);

    fclose(pic);
}
