#include "Menu.h"

#include <iostream>

int main()
{
	try {
		Menu menu;
		menu.start();
	}
	catch (std::string i) {
		std::cout << i << std::endl;
		std::string p = "";
		std::cout << "Entrez qqchose pr quitter" << std::endl;
		std::cin >> p;
	}
	return EXIT_SUCCESS;
}
