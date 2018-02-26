OBJECTS= main.o draw.o display.o matrix.o
LDFLAGS= -lm
CC= gcc

all: $(OBJECTS)
	$(CC) -o main $(OBJECTS)

main.o: work/3/main.c work/3/display.h work/3/draw.h work/3/ml6.h work/3/matrix.h
	$(CC) -g -c work/3/main.c

draw.o: work/3/draw.c work/3/draw.h work/3/display.h work/3/ml6.h work/3/matrix.h
	$(CC) -g -c work/3/draw.c

display.o: work/3/display.c work/3/display.h work/3/ml6.h work/3/matrix.h
	$(CC) -g -c work/3/display.c

matrix.o: work/3/matrix.c work/3/matrix.h
	$(CC) -g -c work/3/matrix.c

run: main
	./main

clean:
	rm *.o *~ main
