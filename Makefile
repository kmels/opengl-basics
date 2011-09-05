CC     = gcc
LIBS   = -lglut -l GLU -l GL -l SDL

opengl-basics:  clean ppmRead.o main.o
	gcc $(CFLAGS) $(LIBS) -o opengl-basics src/main.o src/ppmRead.o

main.o: src/main.c ppmRead.o
	gcc $(LIBS) -c -Wall src/main.c -o src/main.o

ppmRead.o: src/ppmRead.c src/ppmRead.h
	gcc $(LIBS) -c -Wall src/ppmRead.c -o src/ppmRead.o

clean:
	/bin/rm -f *.o; /bin/rm -f opengl-basics
