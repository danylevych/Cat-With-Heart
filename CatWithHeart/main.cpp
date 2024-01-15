#include <iostream>

#include "src/Application/Application.h"

int main()
{
	try
	{
		Application().Run();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}