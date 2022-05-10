#include <iostream>
#include <locale>

#include "PassMng.h"



int main()
{
	setlocale(0, "");
	PassMngr pass;
	pass.firstMassage();
	pass.initFile();
	pass.get_data();
	pass.print_data();

	std::cout << "\n\n\n";
	system("pause");
	return 0;
}