#include <span>
#include <stdexcept>
#include "Parser.hpp"
#include "Toolbox.hpp"
#include "../print.hpp"

namespace parser {

	std::string_view purify(std::string_view line)
	{
		if (line.empty())
			return line;
		line = line.substr(line.find_first_not_of(" \t"));
		if (auto pos = line.find("#"); pos != line.npos)
			line = line.substr(0, pos);
		return line;
	}

	void parseNode(std::string_view line, std::span<std::string_view> vec, ParseInfo& infos)
	{
		if (vec.size() != 1)
			throw std::invalid_argument("invalid node line: " + std::string{line});
		infos.nodes.emplace_back(std::string{vec[0]});
	}

	void parseRail(std::string_view line, std::span<std::string_view> vec, ParseInfo& infos)
	{
		if (vec.size() != 4)
			throw std::invalid_argument("invalid rail line: " + std::string{line});
		infos.rails.emplace_back(std::string{vec[0]}, std::string{vec[1]}, std::stod(std::string{vec[2]}), std::stod(std::string{vec[3]}));
	}

	void parseEvent(std::string_view line, std::span<std::string_view> vec, ParseInfo& infos)
	{
		if (vec.size() != 4)
			throw std::invalid_argument("invalid event line: " + std::string{line});
		infos.events.emplace_back(std::string{vec[0]}, std::stod(std::string{vec[1]}), std::stoul(std::string{vec[2]}), std::string{vec[3]});
	}

	void parseTrain(std::string_view line, std::span<std::string_view> vec, ParseInfo& infos)
	{
		if (vec.size() != 9)
			throw std::invalid_argument("invalid line: " + std::string{line} + ". was it supposed to be a train line?");
		auto start = toolbox::split(vec[7], "h", [](auto s){ return std::string{s}; });
		auto stop = toolbox::split(vec[8], "h", [](auto s){ return std::string{s}; });
		if (start.size() != 2)
			throw std::invalid_argument("invalid format for departure time: " + std::string{vec[7]});
		if (stop.size() != 2)
			throw std::invalid_argument("invalid format for stop duration: " + std::string{vec[8]});
		uint32_t departure = std::stoul(start[0]) + std::stoul(start[1]);
		uint32_t stopTime = std::stoul(stop[0]) + std::stoul(stop[1]);
		infos.trains.emplace_back(std::string{vec[0]}, std::stoul(std::string{vec[1]}), std::stod(std::string{vec[2]}), std::stod(std::string{vec[3]}),
		                          std::stod(std::string{vec[4]}), std::string{vec[5]}, std::string{vec[6]}, departure, stopTime);
	}

	ParseInfo parse(std::istream& input)
	{
		ParseInfo ret;

		while (true) {
			std::string buffer;
			std::getline(input, buffer);
			std::string_view line = buffer;
			line = purify(line);
			if (input.eof())
				break;
			if (line.empty())
				continue;

			print::info(line);
			// split the current line to get needed things.
			auto vec = toolbox::split(line);

			// dispatch to diverse parsers
			if (vec[0] == "Node")
				parseNode(line, std::span(vec).subspan(1, vec.size() - 1), ret);
			else if (vec[0] == "Rail")
				parseRail(line, std::span(vec).subspan(1, vec.size() - 1), ret);
			else if (vec[0] == "Event")
				parseEvent(line, std::span(vec).subspan(1, vec.size() - 1), ret);
			else
				parseTrain(line, std::span(vec), ret);
		}
		return ret;
	}
}
