#pragma once

#include <string>
#include <qstring.h>

class Client 
{
public:
	Client(int id, const std::string& name, const std::string& phone, const std::string& mail, bool active);
	Client(const std::string& name, const std::string& phone, const std::string& mail, bool active);
	Client() = default;
	~Client() = default;

	void setId(int id) { _id = id; };
	int getId() const { return _id; };
	void setName(const std::string& clientName) { _name = clientName; };
	const std::string& getName() const { return _name; };
	void setPhone(const std::string& clientPhone) { _phone = clientPhone; };
	const std::string& getPhone() const { return _phone; };
	void setMail(const std::string& clientMail) { _mail = clientMail; };
	const std::string& getMail() const { return _mail; };
	void setActive(bool active) { _active = active; }
	bool isActive() const { return _active; }

private:
	int _id;
	std::string _name;
	std::string _phone;
	std::string _mail;
	bool _active;
};
