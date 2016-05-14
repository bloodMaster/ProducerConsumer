#include "application.hpp"

// STD
#include <iostream>

int main()
{
	Application app(10, 10, "Results.txt");
	try 
	{
		app.run();
	} catch (const std::exception& ex) 
	{
		std::cerr << "Skipped running of application: " << ex.what();
	}
	return 0;
}

