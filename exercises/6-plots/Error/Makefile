#CFLAGS = `gsl-config --cflags`
CFLAGS = $(shell gsl-config --cflags)
LDLIBS = $(shell gsl-config --libs)

default: erf.gnuplot.png

erf.gnuplot.png: data.txt tabulatedvalues.txt Makefile 
	echo '\
	set terminal png;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x";\
	set ylabel "y";\
	set title "Error function";\
	plot \
	 "$<" using 1:2 with line title "lort"\
	,"$<" using 1:3 with line title "pis"\
	,"$<" using 1:4 with line title "røv"\
	' | gnuplot

data.txt: main
	./$< > $@

main: main.o erf.o

.PHONEY:clean
clean: 
	$(RM) *.o main data.txt
