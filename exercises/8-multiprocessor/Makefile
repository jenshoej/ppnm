CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS += $(shell gsl-config --libs)

plot.pdf: inside_points.txt outside_points.txt
	echo '\
	set terminal pdf;\
	set output "$@";\
	set title "Monte Carlo simulation of the ratio of pi";\
	set size square 1,1;\
	plot \
	"inside_points.txt" using 1:2 with points pointtype 7\
	,"outside_points.txt" using 1:2 with points pointtype 7\
	' | gnuplot

inside_points.txt outside_points.txt: main

clean:
	$(RM) *.o *.txt main *.pdf
