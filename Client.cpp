#include <string>
#include "Client.h"

Client::Client(int id, const std::string& name, const std::string& phone, const std::string& mail)
	: _id(id)
	, _name(name)
	, _phone(phone)
	, _mail(mail)
{
}

Client::Client(const std::string& name, const std::string& phone, const std::string& mail)
	: _name(name)
	, _phone(phone)
	, _mail(mail)
{
}