/*
    work 1: make a ppm
    sierpinski
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "sierpinski.h"

int main(int argc, char **argv) {
    // long pix;
    int *pix = (int*)calloc(512, sizeof(int));
    int *img = (int*)calloc(512, sizeof(int));
    int depth = 6;
    //generate(size,&pix);
    create(depth,pix);
    map(depth,pix,img);
    //print(depth,img);
    save(depth,img);
    free(pix);
    free(img);
}

void create(int depth, int *pix) {
    if (depth < 0 || depth > 6) {
        perror("invalid depth");
        exit(1);
    }

    //depth 0: 1110 length = 4 = 4 << d
    set(pix, 0);
    set(pix, 1);
    set(pix, 2);

    //copy d times: self >>> self self self zero
    for(int d = 0; d < depth; d++) {
        for(int i = 0; i < (2 << (2*d+1)); i++) {
            //copy [i] to  2*2^2d+1[4 << 2*d] + i and 2[4 << d] + i
            //test(pos) ? 1 0 in new loc
            if(get(pix,i)) {
                int t = (4 << (2*d));
                set(pix,t + i);
                set(pix,2*t + i);
            }
            else {
                continue;
                /* calloc'd so already 0
                    clear(pix,(2 << (2*d + 1)) + i);
                    clear(pix,2*(2 << (2*d + 1)) + i);
                */
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
    //size = 4*4^depth = 4 << (2*depth
    //int x = (1 << (depth + 1));
    //int y = (1 << (depth + 1));
    for(int i = 0; i < (4 << (2*depth)); i++) {
        if(get(pix,i)) {
            int t = 4 << (2*depth);
            int d = 2*(depth+1);
            // loop through from i%2/1 to i%64/32
            int x = 0;
            int y = 0;
            while(t > 1) {
            //printf("%d, %d, %d, %d, %d, %d, %d\n",i,d,t,(i%t)/t,(1<<(d/2)),x,y);
                if(d%2) {
                    x += 2*(i%t)/t ? (1<<(d/2)) : 0;
                }
                else {
                    y += 2*(i%t)/t ? (1<<(d/2))/2 : 0;
                }
                d--;
                t/=2;
            }

        //printf("%d, %d\n", x, y);
            set(img,x+y*(2 << depth));
        }

        /*while(d > 0) {
            (t%2) ? (y += ((d/2)%2) ? 1 << d/2 : 0) : (x += ((d/2)%2) ? 1 << d/2 : 0);
            t--;
            d--;
        }
        printf("%d, %d\n", x, y);*/
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
        (get(pix,i)) ? fprintf(pic, "255 255 255 ") : fprintf(pic, "0 0 0 ");
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

/*

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
