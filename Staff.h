#pragma once
#include <string>
#include <qstring.h>

class Staff {
private:
	int id;
	std::string name;
	std::string position;

public:
	Staff(int, std::string, std::string);
	Staff(std::string, std::string, std::string);
	Staff(int);
	Staff();
	~Staff();
	void setId(int);
	void setId(std::string);
	int getId();
	void setName(std::string);
	std::string getName();
	QString getQName();
	void setPosition(std::string);
	std::string getPosition();
	QString getQPosition();
};
