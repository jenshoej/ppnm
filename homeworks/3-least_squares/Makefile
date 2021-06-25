CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)

all: out.txt plot.gnuplot.png 

out.txt: main
	./$< > $@

plot.gnuplot.png: data.txt plotting_data.txt
	echo '\
	set terminal png;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "Time [days]";\
	set ylabel "Activity";\
	set title "Radioactive decay of ThX";\
	plot \
	 "data.txt" using 1:2:3 with yerrorbars title "Measured data" \
	,"plotting_data.txt" using 1:2 with line title "Fit"\
	,"plotting_data.txt" using 1:3 with line title "upper error margin"\
	,"plotting_data.txt" using 1:4 with line title "lower error margin"\
	' | gnuplot

main: main.o ls.c

clean: 
	$(RM) *.o main out.txt params.txt log_data.txt

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)