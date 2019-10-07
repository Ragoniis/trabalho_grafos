default: main.o algorithms.o cleaners.o miscellaneous.o output.o readers.o data_structures.o 
	gcc -Wall -g main.c algorithms.c cleaners.c miscellaneous.c output.c readers.c data_structures.c -o main -lm

clean: 
	rm *.o main	