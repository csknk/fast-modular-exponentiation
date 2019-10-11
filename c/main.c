#include <stdio.h>
#include "integer-input.h"


int fastExp(int b, int e, int m)
{
	int result = 1;
	if (1 & e)
		result = b;
	while (1) {
		if (!e) break;
		e >>= 1;
		b = (b * b) % m;
		if (e & 1)
			result = (result * b) % m;
	}
	return result;
}

int main()
{
	puts("Compute b to the power e modulo m");
	int b = 0, e = 0, m = 0;
	puts("Enter b:");
	getIntegerFromStdin(&b);
	puts("Enter e:");
	getIntegerFromStdin(&e);
	puts("Enter m:");
	getIntegerFromStdin(&m);
	printf("%d to the power %d ≡ %d (mod%d)\n", b, e, fastExp(b, e, m), m);
	return 0;
}
