CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)

all: out.txt plot.gnuplot.png

out.txt: main
	./$< > $@

plot.gnuplot.png: out.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x";\
	set ylabel "y";\
	set title "Cubic spline interpolation";\
	plot \
	"out.txt" using 1:2 with line title "Cubic spline"\
	,"out.txt" using 1:3 with line title "Integration of cubic spline"\
	,"out.txt" using 1:4 with line title "Derivative of cubic spline"\
	' | gnuplot

main: main.o cubic_spline.o

clean: 
	$(RM) *.o main *.txt *.png

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)