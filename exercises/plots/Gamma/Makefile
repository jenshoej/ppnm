CFLAGS = $(shell gsl-config --cflags)
LDLIBS = $(shell gsl-config --libs)
CC = clang

gamma.gnuplot.png: gamma_data.txt tabulated_factorials.txt Makefile
	echo '\
	set terminal png;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x values";\
	set ylabel "y values";\
	set title "Gamma function";\
	plot \
	"$<" using 1:2 with line title "Gsl gamma function"\
	,"tabulated_factorials.txt" using 1:2 with points pointtype 1 title "Tabulated factorials"\
	' | gnuplot

gamma_data.txt: main
	./$< > $@

clean:
	$(RM) *.o main *.png gamma_data.txt

