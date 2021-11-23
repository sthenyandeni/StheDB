all:
	gcc -c -g *.c

main: all
	gcc -o main *.o

run: main
	./main

clean:
	rm -f *.o main