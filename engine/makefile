run: all
	./engine
	convert engine.ppm ../img/engine.png

all: engine.o
	gcc -o engine engine.o

engine.o: engine.c engine.h
	gcc -g -c engine.c

clean:
	rm -f engine engine.o engine.ppm
