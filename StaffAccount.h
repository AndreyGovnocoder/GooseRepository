#pragma once
#include "Staff.h"
#include <qstring.h>

class StaffAccount : public Staff 
{
public:
	StaffAccount() = default;
	~StaffAccount() = default;
	void setLogin(const std::string& login) { _login = login; };
	void setPassword(const std::string& password) { _password = password; };
	const std::string& getLogin() const { return _login; };
	const std::string& getPassword() const { return _password; };

private:
	std::string _login;
	std::string _password;
};