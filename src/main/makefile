all:
	gcc -c -g *.c

main: all print_select
	gcc -m64 -o main *.o

run: main
	./main

print_select:
	yasm -f macho64 -o asm.o print_select.asm

clean:
	rm -f *.o main