//draw
void draw(int p0, int p1, int depth, int *bits);
void subtriangle(int count, int depth, int *bits, int a, int b, int c);
void shell(int depth, int *bits, int a, int b, int c);
void line(int x0, int y0, int x1, int y1, int size, int *bits);

//bits[] accessors
void set(int bits[],  int n);
//void det(int bits[], int n);
int get(int bits[],  int n);

//writing to file
void fprint(FILE *pic, int depth, int *bits);
void save(int size, int *bits);
