#include <string>
#include "Staff.h"

Staff::Staff(const int id, const std::string& name, const std::string& position)
{
	_id = id;
	_name = name;
	_position = position;
}

Staff::Staff(const std::string& id, const std::string& name, const std::string& position)
{
	_id = std::stoi(id);
	_name = name;
	_position = position;
}

Staff::Staff(int id) 
{
	_id = id;
}
