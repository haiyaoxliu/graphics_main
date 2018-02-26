OBJECTS= main.o draw.o display.o matrix.o
LDFLAGS= -lm
CC= gcc

all: $(OBJECTS)
	$(CC) -o main $(OBJECTS)

main.o: main.c display.h draw.h ml6.h matrix.h
	$(CC) -g -c main.c

draw.o: draw.c draw.h display.h ml6.h matrix.h
	$(CC) -g -c draw.c

display.o: display.c display.h ml6.h matrix.h
	$(CC) -g -c display.c

matrix.o: matrix.c matrix.h
	$(CC) -g -c matrix.c

run: main
	./main

clean:
	rm *.o *~
