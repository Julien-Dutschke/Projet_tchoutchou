#pragma once

#include <string>
#include <cstdint>

namespace parser {
	struct Node {
		std::string name;
	};

	struct Rail {
		std::string node1;
		std::string node2;
		double length;
		double speedLimit;
	};

	struct Event {
		std::string name;
		double probability;
		double duration;
		std::string affectedNode;
	};

	struct Train {
		std::string name;
		uint32_t weight; // in tons
		double friction; // unit ???????
		double maxAcceleration; // kiloNewton
		double maxBreakForce; // kiloNewton
		std::string departureNode;
		std::string arrivalNode;

		uint32_t departureTime; // in minutes (ex: 14h30 -> 14x60+30 -> 870)
		uint32_t stopDuration; // in minutes
	};
}
