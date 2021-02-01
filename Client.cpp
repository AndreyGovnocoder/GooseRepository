#include "Client.h"

Client::Client(int id, const std::string& name, const std::string& phone, const std::string& mail, bool active)
	: _id(id)
	, _name(name)
	, _phone(phone)
	, _mail(mail)
	, _active(active)
{
}

Client::Client(const std::string& name, const std::string& phone, const std::string& mail, bool active)
	: _name(name)
	, _phone(phone)
	, _mail(mail)
	, _active(active)
{
}