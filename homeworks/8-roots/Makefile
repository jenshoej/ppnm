CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)

out.txt: main
	./$< > $@

main: main.o newton.o matrix.o integrator.o

clean: 
	$(RM) *.o *.txt main

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)