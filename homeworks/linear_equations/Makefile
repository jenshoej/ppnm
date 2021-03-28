CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)


out.txt: main
	./$< > $@

main: main.o matrix.o

clean: 
	$(RM) *.o *.txt matrix main

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)
