#pragma once
#include <string>
#include <qstring.h>

class Staff 
{
private:
	int _id;
	std::string _name;
	std::string _position;

public:
	Staff(int, const std::string&, const std::string&);
	Staff(const std::string&, const std::string&);
	Staff(int);
	Staff() = default;
	~Staff() = default;
	void setId(const int staffId) { _id = staffId; };
	void setId(const std::string& staffId) { _id = std::stoi(staffId); };
	int getId() const { return _id; };
	void setName(const std::string& staffName) { _name = staffName; };
	const std::string& getName() const { return _name; };
	void setPosition(const std::string& staffPosition) { _position = staffPosition; };
	const std::string& getPosition() const { return _position; };
};
