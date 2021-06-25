CC = GCC-10
CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)

all: out.txt plot.gnuplot.pdf

plot.gnuplot.pdf: out.txt
	echo '\
	set terminal pdf;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x";\
	set ylabel "y";\
	set title "Articial neural network interpolation";\
	plot \
	"$<" index 0 with points title "data"\
	,"$<" index 1 using 1:2 with line title "ann"\
	,"$<" index 1 using 1:3 with line title "ann integral"\
	,"$<" index 1 using 1:4 with line title "ann derivative"\
	' | gnuplot

out.txt: main
	./$< > $@

main: main.o ann.o minimize.o

clean: 
	$(RM) *.o *.txt main *.pdf

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)