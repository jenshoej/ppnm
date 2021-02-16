#include "komplex.h"
#include "stdio.h"
#define TINY 1e-6

int main() {
	komplex a = {1,2}, b = {3,4}
	
	printf("Testing komplex_add method"\n);
	komplex r = komplex_add(a,b);
	komplex R = {4,6}
	komplex_print("a =",a);
	komplex_print("b =",b);
	komplex_print("a + b" = r);

	printf("Testing komplex_sub method"\n);
	komplex r = komplex_sub(b,a);
	komplex_print("a =",a);
	komplex_print("b =",b);
	komplex_print("b - a" = r);

	printf("Testing komplex_new og _set method"\n);
	komplex n = komplex_new(5,6);
	komplex_print("New komplex (5,6) =" n);
	komplex_set(n, 7,8);
	komplex_print("Set komplex to 7,8",n);

	return 0;
}
