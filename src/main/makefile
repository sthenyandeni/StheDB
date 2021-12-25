# all:
# 	gcc -Wall -c -g *.c -lm

#  main: all print_select
# 	gcc -o main *.o

main:
	gcc -no-pie -g -o main *.c *.o -lm

run: main
	./main

# print_select:
# 	yasm -f elf64 -g dwarf2 -o asm.o print_select.asm

clean:
	rm -f *.o main