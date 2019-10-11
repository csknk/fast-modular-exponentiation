#include <iostream>
#include "input.h"

int fastExp(int b, int e, int m)
{
	int result = e & 1 ? b : 1;
	while (e) {
		e >>= 1;
		b = (b * b) % m;
		if (e & 1)
			result = (result * b) % m;
	}
	return result;
}

int main()
{
	int b = 0, e = 0, m = 0;
	inputInt(b, "Please enter b");
	inputInt(e, "Please enter e");
	inputInt(m, "Please enter m");

	std::cout << "Computing " << b << " to the power " << e << " modulo " << m << "\n";
	int r = fastExp(b, e, m);
	std::cout << b << " to the power " << e << " ≡ " << r << " (modulo " << m << ")\n";


	return 0;
}
