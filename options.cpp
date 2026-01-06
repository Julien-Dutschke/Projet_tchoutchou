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
