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
    int *pix = (int*)calloc(2048, sizeof(int));
    int *img = (int*)calloc(2048, sizeof(int));
    int depth = 7;
    create(depth,pix);
    map(depth,pix,img);
    save(depth,img);
    free(pix);
    free(img);
}

void create(int depth, int *pix) {
    if (depth < 0 || depth > 7) {
        perror("invalid depth");
        exit(1);
    }

    set(pix, 0);
    set(pix, 1);
    set(pix, 2);

    for(int d = 0; d < depth; d++) {
        for(int i = 0; i < (2 << (2*d+1)); i++) {
            if(get(pix,i)) {
                int t = (4 << (2*d));
                set(pix,t + i);
                set(pix,2*t + i);
            }
            else {
                continue;
            }
        }
    }
}

void set(int pix[], int n) {
    pix[n/32] |= 1 << (n%32);
}

int get(int pix[], int n) {
    return ((pix[n/32] & (1 << (n%32) ))) ;
}

void map(int depth, int *pix, int *img) {
    for(int i = 0; i < (4 << (2*depth)); i++) {
        if(get(pix,i)) {
            int t = 4 << (2*depth);
            int d = 2*(depth+1);
            int x = 0;
            int y = 0;
            while(t > 1) {
                if(d%2) {
                    x += 2*(i%t)/t ? (1<<(d/2)) : 0;
                }
                else {
                    y += 2*(i%t)/t ? (1<<(d/2))/2 : 0;
                }
                d--;
                t/=2;
            }
            set(img,x+y*(2 << depth));
        }
    }
}

void print(int depth, int *pix) {
    for(int i = 0; i < (4 << (2*depth)); i++) {
        if(i % (2 << depth) == 0) {
            printf("\n");
        }
        (get(pix,i)) ? printf("1 ") : printf("0 ");
    }
    printf("\n");
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
