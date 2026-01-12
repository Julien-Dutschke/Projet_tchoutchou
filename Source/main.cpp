#include <fstream>
#include "Train.hpp"
#include "Parser.hpp"
#include "print.hpp"
#include "options.hpp"


int main(int argc, char *argv[])
{
	clap::parse(argc, argv);

	std::ifstream input("data.test");
	parser::parse(input);

	Train myTrain("Express", 200.0, 0.02, 500.0, 300.0, "Station A", "Station B");
	print::print("Train Name: ", myTrain.getName(), "\n");
	print::print("Weight (tons): ", myTrain.getWeightTons(), "\n");
	return 0;
}
