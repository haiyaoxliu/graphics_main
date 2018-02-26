//draw
void point(int p);
void line(int p0, int p1);
void draw_point(int x0, int y0);
void draw_line(int x0, int y0, int x1, int y1);

//bits[] accessors
void set(int bits[],  int n);
//void det(int bits[], int n);
int get(int bits[],  int n);

//writing to file
void fprint(FILE *pic, int depth, int *bits);
void save(int size, int *bits);
