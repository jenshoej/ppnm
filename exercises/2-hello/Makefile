CC = gcc
CFLAGS = -std=gnu99 -O
LDLIBS = -lm

out.txt: hello
	./hello > out.txt

hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c -o hello.o

hello: hello.o
	$(CC) $(CFLAGS) hello.o -o hello $(LDLIBS)

clean: 
	-rm *o hello
