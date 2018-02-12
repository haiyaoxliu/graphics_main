run: all
	./lines
	convert lines.ppm ../../img/lines.png

all: lines.o
	gcc -o lines lines.o

lines.o: lines.c lines.h
	gcc -g -c lines.c

clean:
	rm -f lines lines.o lines.ppm
