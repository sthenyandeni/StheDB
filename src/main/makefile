all:
	gcc -c -g *.c

main: all print_select
	gcc -o main *.o

run: main
	./main

print_select:
	yasm -f elf64 -g dwarf2 -o asm.o print_select.asm

clean:
	rm -f *.o main