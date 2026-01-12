#pragma once

#include <string>

class Event
{
	private:
		std::string _name;
		double probability;
		std::string localisation;
		double duration; // duration in minutes

	public:
		explicit Event(const std::string& name);

		const std::string& getName() const { return _name; }
};
