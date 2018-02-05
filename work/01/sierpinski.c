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
    int *pix = (int*)calloc(512, sizeof(int));
    int depth = 6;

    create(depth,pix);
    save(depth,pix);

    free(pix);
}

void create(int depth, int *pix) {
    if (depth < 0 || depth > 6) {
        perror("invalid depth");
        exit(1);
    }

    set(pix, 0);
    set(pix, 1);
    set(pix, 2 << depth);

    for(int d = 0; d < depth; d++) {
        for(int r = 0; r < (2 << d); r++) {
            for(int c = 0; c < (2 << d); c++) {
                int t = 2 << d;
                if(get(pix,c+r*(2<<depth))) {
                    set(pix,t + c + r*(2<<depth));
                    set(pix,c + (r+t)*(2<<depth));
                }
                else continue;
            }
        }
    }
}


void set(int pix[], int n) {
    pix[n/32] |= 1 << (n%32);
}

int get(int pix[], int n) {
    return ((pix[n/32] & (1 << (n%32) )));
}

void fprint(FILE *pic, int depth, int *pix) {
    for(int i = 0; i < (4 << (2*depth)); i++) {

        if(i % (2 << depth) == 0) {
            fprintf(pic, "\n");
        }

        int b = (i%255)/4;
        int t = 255-(i%255)/4;
        (get(pix,i)) ? fprintf(pic, "%d %d %d ",t,t,t) : fprintf(pic, "%d %d %d ",b,b,b);
    }
    fprintf(pic, "\n");
}

void save(int depth, int *pix) {
    FILE *pic;
    int size = 2<<depth;
    pic = fopen("sierpinski.ppm", "w");

    fprintf(pic, "P3\n%d %d\n255",size,size);
    fprint(pic, depth, pix);

    fclose(pic);
}
