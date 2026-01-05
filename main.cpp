#include <iostream>
#include "Include/Train.hpp"


int main()
{
	Train myTrain("Express", 200.0, 0.02, 500.0, 300.0, "Station A", "Station B");

	std::cout << "Train Name: " << myTrain.getName() << std::endl;
	return 0;
}