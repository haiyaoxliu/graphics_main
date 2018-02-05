all: sierpinski.o
	gcc -o sierpinski sierpinski.o

sierpinski.o: sierpinski.c sierpinski.h
	gcc -g -c sierpinski.c

run: all
	./sierpinski

clean:
	rm -f sierpinski sierpinski.o sierpinski.ppm
