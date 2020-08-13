#pragma once

#include <string>
#include <qstring.h>

class Client {
private:
	int id;
	std::string name;
	std::string phone;
	std::string mail;

public:
	Client(int, std::string, std::string, std::string);
	Client(std::string, std::string, std::string, std::string);
	Client();
	~Client();
	void setId(int);
	void setId(std::string);
	int getId();
	void setName(std::string);
	std::string getName();
	QString getQName();
	void setPhone(std::string);
	std::string getPhone();
	QString getQPhone();
	void setMail(std::string);
	std::string getMail();
	QString getQMail();
};
