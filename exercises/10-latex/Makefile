CFLAGS = -O1 -std=gnu11
CFLAGS += $(shell gsl-config --cflags)
LDLIBS = -lm
LDLIBS += $(shell gsl-config --libs)

all: exp.pdf out.txt 

exp.pdf: report.tex plot.gnuplot.pdf
	pdflatex $<
	pdflatex $<

out.txt: main
	./$< > $@

plot.gnuplot.pdf: out.txt
	echo '\
	set terminal pdf;\
	set output "$@";\
	set key top left;\
	set tics out;\
	set xlabel "x";\
	set ylabel "exp(x)";\
	set title "Exponential function";\
	plot \
	"$<" using 1:2 with line title "My exp"\
	,"$<" using 1:3 with line title "math.h exp"\
	' | gnuplot

main: main.o

clean: 
	$(RM) *.o main *.txt report.pdf report.log report.aux *.png

test:
	@echo $(CFLAGS)
	@echo $(LDLIBS)