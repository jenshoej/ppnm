CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --ldlibs)

out.txt: main
	./$< > $@

clean: 
	$(RM) *.o main

test: 
	@echo $(CFLAGS)
	@echo $(LDLIBS)