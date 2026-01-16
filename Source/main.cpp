#include <exception>
#include <fstream>
#include "Train.hpp"
#include "Parser.hpp"
#include "print.hpp"
#include "options.hpp"

// returns 0 on success.
// returns 1 on known failure
// returns 2 on unknown failure (if a weird exception happens)
int main(int argc, char *argv[])
{
	try {
		const clap::Options options = clap::parse(argc, argv);

		for (const auto& file : options.inputs) {
			std::ifstream input(std::string{file});
			parser::parse(input);
		}

		Train myTrain("Express", 200.0, 0.02, 500.0, 300.0, "Station A", "Station B");
		print::print("Train Name: ", myTrain.getName(), "\n");
		print::print("Weight (tons): ", myTrain.getWeightTons(), "\n");
	} catch (const std::exception&e) {
		print::err(e.what());
		return 1;
	} catch (...) {
		print::err("Unhandled error occured.");
		return 2;
	}
	return 0;
}
