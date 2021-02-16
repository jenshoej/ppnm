out.txt: komplex
	./ komplex > out.txt

komplex.o: komplex.c
	gcc -c komplex.c -o komplex.o

komplex: komplex.o
	gcc math.o -o math -lm

clean:
	-rm *.o

