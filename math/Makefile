out.txt: math
	./ math > out.txt

math.o: math.c
	gcc -c math.c -o math.o

math: math.o
	gcc math.o -o math -lm

clean:
	-rm *.o out*
