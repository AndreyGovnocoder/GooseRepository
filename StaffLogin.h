#pragma once
#include "Staff.h"
#include <string>
#include <qstring.h>

class StaffLogin : public Staff 
{
private:
	std::string _login;
	std::string _password;

public:
	StaffLogin() = default;
	~StaffLogin() = default;
	void setLogin(const std::string& login) { _login = login; };
	void setPassword(const std::string& password) { _password = password; };
	const std::string& getLogin() const { return _login; };
	const std::string& getPassword() const { return _password; };
};