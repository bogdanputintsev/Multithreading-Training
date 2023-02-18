#include <iostream>
#include "source/Factory.h"

int main()
{
	auto factory = Factory();
	factory.run();
	
	return EXIT_SUCCESS;
}