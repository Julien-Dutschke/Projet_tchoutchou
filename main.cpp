#include <iostream>
#include "Include/Train.hpp"


int main()
{
	Train myTrain("Express", 200.0, 0.02, 500.0, 300.0, "Station A", "Station B");
	print("Train Name: ", myTrain.getName(), "\n");
	print("Weight (tons): ", myTrain.getWeightTons(), "\n");
	return 0;
}