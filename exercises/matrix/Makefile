CFLAGS = -O1 -std=gnu11 #-DNDEBUG
CFLAGS += $(shell gsl-config --cflags)
LDLIBS += $(shell gsl-config --libs)

all: out.txt

out.txt: matrix
	./$< > $@

clean: 
	$(RM) *.o *.txt matrix

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)
