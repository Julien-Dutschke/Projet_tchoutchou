#include <filesystem>
#include <stdexcept>
#include <string_view>
#include "options.hpp"
#include "print.hpp"

using namespace print;

// commandLineArgumentParser, but shorter.
namespace clap {

	// needs to be kept up to date, as it is not auto generated.
	void help(std::string_view binary)
	{
		println("Usage: ", binary, " <arguments>");
		println("\t-h | --help:\tThis message!");
		println("\t-i | --input <input file> :\tinput file containing train, rails, nodes, and (or) events.");
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

	void validate(Options& options)
	{
		if (options.inputs.empty())
			throw std::invalid_argument("at least one input is required.");
		for (auto& input : options.inputs) {
			if (!std::filesystem::exists(input))
				throw std::invalid_argument(std::string{input} + " does not exist.");
			if (!std::filesystem::is_regular_file(input))
				throw std::invalid_argument(std::string{input} + " is not a regular file.");
		}
	}

	template <typename... Args>
	bool oneOf(std::string_view comp, Args... args)
	{
		return ((comp == args) || ...);
	}

	Options parse(int argc, char *argv[])
	{
		Options options;
		int unknownArguments = 0;
		bool skipPossible = false;
		bool skip = false;
		// loop on every arguments.
		for (int i = 1; i < argc; ++i) {
			// allows to skip arguments when needed.
			if (skipPossible && skip) {
				skipPossible = skip = false;
				continue;
			}
			skip = false;
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
				skipPossible = false;
			} else if (i  + 1 < argc) {
				value = argv[i + 1];
				skipPossible = true;
			}

			// actual arguments. set the "skip" variable here if you want to skip because you had an argument.
			if (oneOf(current, "help", "h"))
				help(argv[0]);
			else if (oneOf(current, "input", "i")) {
				if (value.empty())
					throw std::invalid_argument("input requires a value.");
				options.inputs.emplace_back(value);
				skip = true;
			} else {
				warn("Unknown argument ", current, " with potential value ", value);
				++unknownArguments;
			}
		}
		if (unknownArguments != 0)
			err("found ", unknownArguments, " unknown argument(s), exiting now.");
		validate(options);
		return options;
	}
}
