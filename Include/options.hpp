#pragma once
#include <string_view>
#include <vector>

namespace clap {
	struct Options {
		std::vector<std::string_view> inputs;
	};

	Options parse(int argc, char *argv[]);
}
