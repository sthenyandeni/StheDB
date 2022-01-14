all:
	cp ./original/* ./
	gcc -Wall -c -g *.c -lm

 main: all
	gcc -o main *.o

# main:
# 	cp ./original/* ./
# 	gcc -g -o main *.c -lm

run: main
	./main

parser:
	cd parser
	rm -f *.o main
	gcc -Wall -c -g *.c
	gcc -o main *.o
	cd ..
	./main

# print_select:
# 	yasm -f elf64 -g dwarf2 -o asm.o print_select.asm

clean:
	rm -f *.o main