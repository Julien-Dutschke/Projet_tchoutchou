#pragma once

#include <istream>
#include <vector>
#include "ParserTypes.hpp"

namespace parser {
	struct ParseInfo {
		std::vector<Node> nodes;
		std::vector<Rail> rails;
		std::vector<Event> events;
		std::vector<Train> trains;
	};

	ParseInfo parse(std::istream& input);
}
