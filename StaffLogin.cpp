#include "StaffLogin.h"

StaffLogin::StaffLogin(){}

StaffLogin::~StaffLogin(){}

void StaffLogin::setLogin(std::string login) {
	StaffLogin::login = login;
}

void StaffLogin::setPassword(std::string password) {
	StaffLogin::password = password;
}

std::string StaffLogin::getLogin() {
	return StaffLogin::login;
}

QString StaffLogin::getQLogin() {
	return QString::fromStdString(StaffLogin::login);
}

std::string StaffLogin::getPassword() {
	return StaffLogin::password;
}

QString StaffLogin::getQPassword() {
	return QString::fromStdString(StaffLogin::password);
}