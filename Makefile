default: test2.o algorithms3_matrix.o algorithms3_list.o algorithms2_matrix.o algorithms2_list.o algorithms.o cleaners.o miscellaneous.o output.o readers.o data_structures.o 
	gcc -O3 test2.c algorithms3_matrix.c algorithms3_list.c algorithms2_matrix.c algorithms2_list.c algorithms.c cleaners.c miscellaneous.c output.c readers.c data_structures.c -o main -lm

data_structures.o : data_structures.c data_structures.h
	gcc -O3 -c data_structures.c

readers.o : readers.c readers.h
	gcc -O3 -c readers.c

output.o : output.c output.h
	gcc -O3 -c output.c

miscellaneous.o : miscellaneous.c miscellaneous.h
	gcc -O3 -c miscellaneous.c

cleaners.o : cleaners.c cleaners.h
	gcc -O3 -c cleaners.c

algorithms.o : algorithms.c algorithms.h
	gcc -O3 -c algorithms.c

algorithms2_list.o : algorithms2_list.c algorithms2_list.h
	gcc -O3 -c algorithms2_list.c

algorithms2_matrix.o : algorithms2_matrix.c algorithms2_matrix.h
	gcc -O3 -c algorithms2_matrix.c


clean: 
	rm *.o main	
