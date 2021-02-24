CFLAGS = $(shell gsl-config --cflags)
LDLIBS = $(shell gsl-config --libs)
CC = clang

gamma.gnuplot.pdf: gamma_data.txt tabulated_factorials.txt Makefile
	echo '\
	set terminal pdf;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x values";\
	set ylabel "y values";\
	set title "Gamma function";\
	set title "Gamma function";\
	plot \
	"$<" using 1:2 with line title "Gsl"\
	,"$<" using 1:3 with line title "tgamma"\
	,"tabulated_factorials.txt" using 1:2 with points pointtype 8 title "Tabulated factorials"\
	' | gnuplot

gamma_data.txt: main
	./$< > $@

main: main.o

clean:
	$(RM) *.o main *.pdf gamma_data.txt

