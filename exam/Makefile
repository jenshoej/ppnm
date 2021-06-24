CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)

all: out.txt plot1.gnuplot.pdf plot2.gnuplot.pdf

out.txt: main
	./$< > $@

plot1.gnuplot.pdf: aspline_data_1.txt cspline_data_1.txt data_points_1.txt
	echo '\
	set terminal pdf;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x";\
	set ylabel "y";\
	set title "Cubic spline interpolation";\
	plot \
	"cspline_data_1.txt" using 1:2 with line title "Cubic spline"\
	,"aspline_data_1.txt" using 1:2 with line title "Akima sub spline"\
	,"data_points_1.txt" using 1:2 with points title "Data points"\
	' | gnuplot

plot2.gnuplot.pdf: aspline_data_2.txt cspline_data_2.txt data_points_2.txt
	echo '\
	set terminal pdf;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x";\
	set ylabel "y";\
	set title "Cubic spline interpolation of random points";\
	plot \
	"cspline_data_2.txt" using 1:2 with line title "Cubic spline"\
	,"aspline_data_2.txt" using 1:2 with line title "Akima sub spline"\
	,"data_points_2.txt" using 1:2 with points title "Data points"\
	' | gnuplot

main: main.o aspline.o cspline.o

clean: 
	$(RM) *.o *.txt main *.pdf

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)