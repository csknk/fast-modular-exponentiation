#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <typeinfo>
#include <limits>

void inputInt(int& input, const char* label)
{
	while (1) {
		std::cout << label << ":\n";
		if (!(std::cin >> input)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
}
#endif
