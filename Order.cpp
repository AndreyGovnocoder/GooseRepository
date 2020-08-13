#include "Order.h"

Order::Order() {
}

Order::~Order() {}

void Order::setId(int newId) {
	Order::id = newId;
}

void Order::setDate(QDate newDate) {
	Order::date = newDate;
}

void Order::setClient(Client newClient) {
	Order::client = newClient;
}

void Order::setPayment(std::string newPayment) {
	Order::payment = newPayment;
}

void Order::setAmount(std::string newAmount) {
	Order::amount = newAmount;
}

void Order::setManager(Staff newManager) {
	Order::manager = newManager;
}

void Order::setDesigner(Staff newDesigner) {
	Order::designer = newDesigner;
}

void Order::setPositionsList(std::vector<OrderPosition> newPositionsList) {
	Order::positionsList = newPositionsList;
}

void Order::setAvailability(std::string newAvailability) {
	Order::availability = newAvailability;
}

void Order::setRemark(std::string newRemark) {
	Order::remark = newRemark;
}

void Order::setLoginCreate(int loginId) {
	Order::loginCreate = loginId;
}

void Order::setLoginEdit(int loginId) {
	Order::loginEdit = loginId;
}

void Order::setLoginAvailability(int loginId) {
	Order::loginAvailability = loginId;
}

void Order::setDateTimeCreate(QDateTime dateTime) {
	Order::dateTimeCreate = dateTime;
}

void Order::setDateTimeEdit(QDateTime dateTime) {
	Order::dateTimeEdit = dateTime;
}

void Order::setDateTimeAvailability(QDateTime dateTime) {
	Order::dateTimeAvailability = dateTime;
}

int Order::getId() {
	return Order::id;
}

QDate Order::getDate() {
	return Order::date;
}

Client Order::getClient() {
	return Order::client;
}

std::string Order::getPayment() {
	return Order::payment;
}

QString Order::getQPayment() {
	return QString::fromStdString(Order::payment);
}

std::string Order::getAmount() {
	return Order::amount;
}

QString Order::getQAmount() {
	return QString::fromStdString(Order::amount);
}

Staff Order::getManager() {
	return Order::manager;
}

Staff Order::getDesigner() {
	return Order::designer;
}

std::vector<OrderPosition> Order::getPositionsList() {
	return Order::positionsList;
}

std::string Order::getAvailability() {
	return Order::availability;
}

QString Order::getQAvailability() {
	return QString::fromStdString(Order::availability);
}

std::string Order::getRemark() {
	return Order::remark;
}

QString Order::getQRemark() {
	return QString::fromStdString(Order::remark);
}

int Order::getLoginCreate() {
	return Order::loginCreate;
}

int Order::getLoginEdit() {
	return Order::loginEdit;
}

int Order::getLoginAvailability() {
	return Order::loginAvailability;
}

QDateTime Order::getDateTimeCreate() {
	return Order::dateTimeCreate;
}

QDateTime Order::getDateTimeEdit() {
	return Order::dateTimeEdit;
}

QDateTime Order::getDateTimeAvailability() {
	return Order::dateTimeAvailability;
}