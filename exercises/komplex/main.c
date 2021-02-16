#include "komplex.h"
#include "stdio.h"
#define TINY 1e-6

int main() {
	komplex a = {1,2}, b = {3,4};
	
	printf("Testing komplex_add method\n");
	komplex add = komplex_add(a,b);
	komplex_print("a =",a);
	komplex_print("b =",b);
	komplex_print("a + b =",add);

	printf("Testing komplex_sub method\n");
	komplex sub = komplex_sub(b,a);
	komplex_print("a =",a);
	komplex_print("b =",b);
	komplex_print("b - a =", sub);

	printf("Testing komplex_new og _set method\n");
	komplex new = komplex_new(5,6);
	komplex_print("New komplex (5,6) =",new);
	komplex_set(&new, 7, 8);
	komplex_print("Set komplex to 7,8",new);

	return 0;
}
