#include "OrderPosition.h"

OrderPosition::OrderPosition() {}

OrderPosition::~OrderPosition() {}

void OrderPosition::setIdOrder(int newIdOrder) {
	OrderPosition::idOrder = newIdOrder;
}

void OrderPosition::setIdPosition(int newIdPosition) {
	OrderPosition::idPosition = newIdPosition;
}

void OrderPosition::setDescription(std::string newDescription) {
	OrderPosition::description = newDescription;
}

void OrderPosition::setQuantity(std::string newQuantity) {
	OrderPosition::quantity = newQuantity;
}

void OrderPosition::setIssue(std::string newIssue) {
	OrderPosition::issue = newIssue;
}

int OrderPosition::getIdOrder() {
	return OrderPosition::idOrder;
}

int OrderPosition::getIdPosition() {
	return OrderPosition::idPosition;
}

std::string OrderPosition::getDescription() {
	return OrderPosition::description;
}

QString OrderPosition::getQDescription() {
	return QString::fromStdString(OrderPosition::description);
}

std::string OrderPosition::getQuantity() {
	return OrderPosition::quantity;
}

QString OrderPosition::getQQuantity() {
	return QString::fromStdString(OrderPosition::quantity);
}

std::string OrderPosition::getIssue() {
	return OrderPosition::issue;
}

QString OrderPosition::getQIssue() {
	return QString::fromStdString(OrderPosition::issue);
}