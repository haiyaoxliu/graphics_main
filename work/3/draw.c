#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z
Returns:
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
	if( points->lastcol == pobints->cols ) {
		grow_matrix(points, points->lastcol + 2);
	}
	points->m[0][ points->lastcol ] = x;
	points->m[1][ points->lastcol ] = y;
	points->m[2][ points->lastcol ] = z;
	points->m[3][ points->lastcol ] = 1;
	points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns:
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points,
	       double x0, double y0, double z0,
	       double x1, double y1, double z1) {
	add_point( points, x0, y0, z0 );
	add_point( points, x1, y1, z1 );
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c
Returns:
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
	if(points->lastcol < 2) return;
	int p;
	for(p = 0; p < points->lastcol - 1; p += 2) {
		draw_line(points->m[0][p], points->m[1][p], points->m[0][p+1], points->m[1][p+1], s, c);
	}
}




void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	int dx, dy, tx, ty, xinc, yinc, D, T;
    tx = (dx = (xinc = x0<x1 ? 1 : -1) * (x1-x0)) << 1;
    ty = (dy = (yinc = y0<y1 ? 1 : -1) * (y1-y0)) << 1;

    //init error
    D = (dx>dy ? -dx : dy);

    while(1) {

        //plot current point
        plot(s, c, x0, y0);

        //drawn entire line >>> quit
        if (x0 == x1 && y0 == y1) break;

        //error accumulation
        T = D;
        if (T < tx) { D += ty; x0 += xinc; }
        if (T > -ty) { D -= tx; y0 += yinc; }

    }

/*
  int x, y, d, A, B;
  //swap points if going right -> left
  int xt, yt;
  if (x0 > x1) {
    xt = x0;
    yt = y0;
    x0 = x1;
    y0 = y1;
    x1 = xt;
    y1 = yt;
  }

  x = x0;
  y = y0;
  A = 2 * (y1 - y0);
  B = -2 * (x1 - x0);

  //octant 1
  if ( abs(x1 - x0) >= abs(y1 - y0) ) {

    //octant 1
    if ( A > 0 ) {
      d = A + B/2; //not really division since B = 2B

      while ( x < x1 ) {
        plot( s, c, x, y );
        if ( d > 0 ) {
          y+= 1;
          d+= B;
        }
        x++;
        d+= A;
      } //end octant 1 while
      plot( s, c, x1, y1 );
    } //end octant 1
  }
*/
} //end draw_line
