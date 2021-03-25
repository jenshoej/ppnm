CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)

all: out.txt

out.txt: main
	./$< > $@

main: main.o matrix.o

clean: 
	$(RM) *.o *.txt matrix

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)
