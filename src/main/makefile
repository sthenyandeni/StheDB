all:
	gcc -c */*.c

main: all
	gcc -o main main.o */*.o

run:
	./main

clean:
	rm -f *.o main