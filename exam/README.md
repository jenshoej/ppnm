My student number is 201905866, and I received the project to implement the Akima sub spline.

The Akima sub spline is a cubic piecewise polynomial spline, which divides the intervals. Cubic splines are subject the wiggles
and the Akima sub spline sacrifices maximal differentiability, to minimize these wiggles. Instead of the continuity condition of the 
second derivative, the derivatives are instead chosen as a linear combination of the nearest slopes.

I have in this program implemented both a regular cubic spline, and the Akima sub spline, and made two plots, plot1.gnuplot.pdf and plot2.gnuplot.pdf, 
of random points, to demonstrate the differences, and minimization of the wiggles that occurs with the cubic spline.

As described in the book, I have chosen the two first and two last derivatives, S', of the spline as 

S[1]' = p[1]
S[2]' = 0.5*(p[1] + p[2])
S[n]' = p[n-1]
S[n-1]' = 0.5*(p[n-1 + p[n-2])

Where p = (y[n+1] - y[n]) / (x[n+1] - x[n]) is the linear slope of the spline.

They could've been chosen otherwise, but as suggested by the book, I have used these conditions.

What I found is, that the Akima sub spline does indeed have much smaller, close to none actually, wiggles, compared to the regular cubic spline.