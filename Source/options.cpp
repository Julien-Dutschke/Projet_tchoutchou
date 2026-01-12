#include <string_view>
#include "print.hpp"

using namespace print;

// commandLineArgumentParser, but shorter.
namespace clap {

	// needs to be kept up to date, as it is not auto generated.
	void help(std::string_view binary)
	{
		println("Usage: ", binary, " <arguments>");
		println("\t-h | --help:\tThis message!");
		println("");
		println("Format of input data (arguments in '<>' blocks are mandatory):");
		println("Nodes:");
		println("\tNode <Node name>");
		println("Rails:");
		println("\tRail <Node 1> <Node 2> <Length (in km)> <Speed limit (in kmph)>");
		println("Events:");
		println("\tEvent <Event name> <Probability (from 0 to 1)> <Duration> <Affected node>");
		println("Trains:");
		println("\t<Train name> <weight> <Friction coefficient> <Max acceleration force (in KN)> <max break force (in KN)> <departure node> <arrivan node> <departure time> <stop time>");
		println("");
		println("times follow this format: <hour>h<minutes> (ex: 14h30, 00h20)");
		println("rail connected nodes need to already exist, or to be declared in the same file.");
		println("empty lines are ignored. everything after a '#' character is considered a comment, and is therefore deleted.");
		println("whitespace at the beginning of a line will be ignored. inside lines, separation character is a space, and not a tab.");
		println("names can be quoted with double quotes (\" character), and will be considered as one unique string.");
		exit(0);
	}

	void parse(int argc, char *argv[])
	{
		int skip = 0;
		int unknownArguments = 0;
		// loop on every arguments.
		for (int i = 1; i < argc; ++i) {
			// allows to skip arguments when needed.
			if (skip > 0) {
				--skip;
				continue;
			}
			// trim the current arguments of any leading '-'.
			// allows us to be posix and gnu compliant at the same time.
			std::string_view current = argv[i];
			if (auto pos = current.find_first_not_of("-"); pos != current.npos)
				current = current.substr(pos);

			// gets the value of the argument if it exists.
			// if it does not, accesses the next 
			std::string_view value = "";
			if (auto pos = current.find_first_of("="); pos != current.npos) {
				value = current.substr(pos + 1);
				current = current.substr(0, pos);
			} else if (i  + 1 < argc)
				value = argv[i + 1];

			// actual arguments. set the "skip" variable here if you want to skip because you had an argument.
			if (current == "help")
				help(argv[0]);
			else {
				warn("Unknown argument ", current, " with potential value ", value);
				++unknownArguments;
			}
		}
		if (unknownArguments != 0)
			err("found ", unknownArguments, " unknown argument(s), exiting now.");
	}
}
