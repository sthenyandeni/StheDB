clean:
	rm -f *.o main

build:
	gcc -Wall -c -g *.c

run: clean build
	gcc -o main *.o
	./main