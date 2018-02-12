run: all
	./lines
	convert lines.ppm img/lines.png

all: lines.o
	gcc -o lines lines.o

lines.o: work/2/lines.c work/2/lines.h
	gcc -g -c work/2/lines.c

clean:
	rm -f lines lines.o lines.ppm
