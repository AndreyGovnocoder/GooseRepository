#include <string>
#include "Staff.h"

Staff::Staff(int id, std::string name, std::string position) {
	Staff::setId(id);
	Staff::setName(name);
	Staff::setPosition(position);
}

Staff::Staff(std::string id, std::string name, std::string position) {
	Staff::setId(std::stoi(id));
	Staff::setName(name);
	Staff::setPosition(position);
}

Staff::Staff(int id) {
	Staff::setId(id);
}

Staff::Staff() {}

Staff::~Staff() {
	//деструктор
}

void Staff::setId(int staffId) {
	Staff::id = staffId;
}

void Staff::setId(std::string staffId) {
	Staff::id = std::stoi(staffId);
}

int Staff::getId() {
	return Staff::id;
}

void Staff::setName(std::string staffName) {
	Staff::name = staffName;
}

std::string Staff::getName() {
	return Staff::name;
}

QString Staff::getQName() {
	return QString::fromStdString(Staff::name);
}

void Staff::setPosition(std::string staffPosition) {
	Staff::position = staffPosition;
}

std::string Staff::getPosition() {
	return Staff::position;
}

QString Staff::getQPosition() {
	return QString::fromStdString(Staff::position);
}


