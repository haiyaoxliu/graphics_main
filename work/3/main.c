#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main(int argv, char** argc) {

  screen s;
  clear_screen(s);

  color c;
  c.red = 255;
  c.green = 255;
  c.blue = 255;

  struct matrix *a = new_matrix(4, 4);
  struct matrix *b = new_matrix(4, 4);

  add_edge(b, 1, 1, 0, 2, 3, 0);
  add_edge(b, 5, 8, 0, 13, 21, 0);
  print_matrix(b);
  printf("\n========================a\n");

  add_edge(a, 5, 4, 0, 7, 5, 0);
  add_edge(b, 2, 9, 0, 6, 1, 0);
  print_matrix(a);
  printf("\n========================b\n");

  matrix_mult(a, b);
  print_matrix(b);
  printf("\n========================mult\n");

  ident(a);
  print_matrix(a);
  //print_matrix(b);
  printf("\n========================ident\n");

  free_matrix(a);
  free_matrix(b);
  //double size = 500;

  struct matrix *edges = new_matrix(4, 256);
  //print_matrix(edges);
  srand(time(NULL));
  for(int i = 0; i < 128; i++) {
      add_edge(edges,rand()%512,rand()%512,0,rand()%512,rand()%512,0);
  }
  draw_lines(edges,s,c);

  /*
  add_edge(edges, 0, 0, 0, 0, 100, 0);
  add_edge(edges, 0, 100, 0, 100, 100, 0);
  add_edge(edges, 100, 100, 0, 100, 0, 0);
  add_edge(edges, 100, 0, 0, 0, 0, 0);
  display(s);
  */
  save_extension(s, "work3.png");
  free_matrix( edges );
}
