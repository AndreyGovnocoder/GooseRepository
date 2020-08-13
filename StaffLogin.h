#pragma once
#include "Staff.h"
#include <string>
#include <qstring.h>

class StaffLogin : public Staff {
private:
	std::string login;
	std::string password;

public:
	StaffLogin();
	~StaffLogin();
	void setLogin(std::string);
	void setPassword(std::string);
	std::string getLogin();
	std::string getPassword();
	QString getQLogin();
	QString getQPassword();
};