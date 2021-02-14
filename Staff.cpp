#include <string>
#include "Staff.h"

Staff::Staff(const int id, const std::string& name, const std::string& position, bool active)
	: _id(id)
	, _name(name)
	, _position(position)
	, _active(active)
{
}

Staff::Staff(const std::string& name, const std::string& position, bool active)
	: _name(name)
	, _position(position)
	, _active(active)
{
}

Staff::Staff(int id) 
	: _id(id)
{
}
