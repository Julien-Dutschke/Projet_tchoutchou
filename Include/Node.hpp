#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node
{
	private:
		std::string _name;

	public:
		explicit Node(const std::string& name);

		const std::string& getName() const { return _name; }
};

#endif // NODE_HPP
