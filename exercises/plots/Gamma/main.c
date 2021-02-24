#include<stdio.h>
#include<math.h>
#include<gsl/gsl_sf_gamma.h>

double mygamma(double x){
///single precision gamma function (Gergo Nemes, from Wikipedia)
if(x<0) return M_PI/sin(M_PI*x)/mygamma(1-x);
if(x<9) return mygamma(x+1)/x;
double lnmygamma=x*log(x+1/(12*x-1/x/10))-x+log(2*M_PI/x)/2;
return exp(lnmygamma);
}


int main() {
	double xmin=1;
	double xmax=6;
	for(double x=xmin;x<=xmax;x+=1.0/4) {
		printf("%10g %10g %10g %10g \n",x,gsl_sf_gamma(x),tgamma(x),mygamma(x));
	}
return 0;
}
