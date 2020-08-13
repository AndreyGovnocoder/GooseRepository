#pragma once
#include <string>
#include <qstring.h>

class OrderPosition {
private:
	int idOrder;
	int idPosition;
	std::string description;
	std::string quantity;
	std::string issue;

public:
	OrderPosition();
	~OrderPosition();
	void setIdOrder(int);
	void setIdPosition(int);
	void setDescription(std::string);
	void setQuantity(std::string);
	void setIssue(std::string);
	int getIdOrder();
	int getIdPosition();
	std::string getDescription();
	QString getQDescription();
	std::string getQuantity();
	QString getQQuantity();
	std::string getIssue();
	QString getQIssue();
};
