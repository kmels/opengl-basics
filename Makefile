CC     = gcc
LIBS   = -lglut -l GLU -l GL 

form-shifter:  clean main.o
	gcc $(CFLAGS) $(LIBS) -o opengl-basics src/main.o

main.o: src/main.c
	gcc $(LIBS) -c -Wall  src/main.c -o src/main.o
clean:
	/bin/rm -f *.o; /bin/rm -f opengl-basics
