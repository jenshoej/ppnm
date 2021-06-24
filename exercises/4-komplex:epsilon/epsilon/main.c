#include<stdio.h>
#include<limits.h>
#include<float.h>

int main(){

   int i = 0;
   while(i+1>i){
      i++;
   }
   printf("WHILE LOOP MAX INT = %d\n", i);

   printf("INT_MAX    = %d\n", INT_MAX);
   
   // WHILE LOOP
   printf("\n");
   printf("WHILE LOOPS\n");

   float x = 1;
   while(1+x != 1){ x /= 2; }
   x *= 2;
   printf("epsilon (float)  = %.10g\n", x);
   
   double y = 1;
   while(1+y != 1){ y /= 2; }
   y *= 2;
   printf("epsilon (double) = %.10lg\n", y);
  
   long double z = 1;
   while(1+z != 1){ z /= 2; }
   z *= 2;
   printf("epsilon (long)   = %.10Lg\n", z);


   //FOR LOOP 
    printf("\n");
   printf("FOR LOOPS\n");

   float e;
   for(e = 1; 1+e != 1; e/=2){}
   e *= 2;
   printf("epsilon (float)  = %.10g\n", e);
   
   double f;
   for(f = 1; 1+f != 1; f/=2){}
   f *= 2;
   printf("epsilon (double) = %.10lg\n", f);
  
   long double g;
   for(g = 1; 1+g != 1; g/=2){}
   g *= 2;
   printf("epsilon (long)   = %.10Lg\n", g);    



   // MACHINE PRECISION USING DO LOOP
    printf("\n");
   printf("DO LOOPS\n");

   float a = 1;
   do{ a/=2; }
   while( 1+a != 1 );
   a *= 2;
   printf("epsilon (float)  = %.10g\n", a);
   
   double b = 1;
   do{ b/=2; }
   while( 1+b != 1 );
   b *= 2;
   printf("epsilon (double) = %.10lg\n", b);
  
   long double c = 1;
   do{ c/=2; }
   while( 1+c != 1 );
   c *= 2;
   printf("epsilon (long)   = %.10Lg\n", c);

    
   printf("\n");
   // SYSTEM PRECISION
   printf("SYSTEM PRECISION\n");
   printf("epsilon (float)  = %.10g\n", FLT_EPSILON);
   printf("epsilon (double) = %.10lg\n", DBL_EPSILON);
   printf("epsilon (long)   = %.10Lg\n", LDBL_EPSILON);

    return 0;
}