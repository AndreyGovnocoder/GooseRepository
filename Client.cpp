#include <string>
#include "Client.h"

Client::Client(int id, std::string name, std::string phone, std::string mail) {
	Client::setId(id);
	Client::setName(name);
	Client::setPhone(phone);
	Client::setMail(mail);
}

Client::Client(std::string id, std::string name, std::string phone, std::string mail) {
	Client::setId(std::stoi(id));
	Client::setName(name);
	Client::setPhone(phone);
	Client::setMail(mail);
}

Client::Client() {}

Client::~Client() {}

void Client::setId(int clientId) {
	Client::id = clientId;
}

void Client::setId(std::string clientId) {
	Client::id = std::stoi(clientId);
}

int Client::getId() {
	return Client::id;
}

void Client::setName(std::string clientName) {
	Client::name = clientName;
}

std::string Client::getName() {
	return Client::name;
}

QString Client::getQName() {
	return QString::fromStdString(Client::name);
}

void Client::setPhone(std::string clientPhone) {
	Client::phone = clientPhone;
}

std::string Client::getPhone() {
	return Client::phone;
}

QString Client::getQPhone() {
	return QString::fromStdString(Client::phone);
}

void Client::setMail(std::string clientMail) {
	Client::mail = clientMail;
}

std::string Client::getMail() {
	return Client::mail;
}

QString Client::getQMail() {
	return QString::fromStdString(Client::mail);
}
