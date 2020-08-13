#pragma once
#include <string>
#include <qdatetime.h>
#include <qstring.h>
#include "Client.h"
#include "Staff.h"
#include "OrderPosition.h"

class Order {
private:
	int id;
	QDate date;
	Client client;
	std::string payment;
	std::string amount;
	Staff manager;
	Staff designer;
	std::vector<OrderPosition> positionsList;
	std::string availability;
	std::string remark;
	int loginCreate;
	int loginEdit;
	int loginAvailability;
	QDateTime dateTimeCreate;
	QDateTime dateTimeEdit;
	QDateTime dateTimeAvailability;

public:

	Order();
	~Order();
	void setId(int);
	void setDate(QDate);
	void setClient(Client);
	void setPayment(std::string);
	void setAmount(std::string);
	void setManager(Staff);
	void setDesigner(Staff);
	void setPositionsList(std::vector<OrderPosition>);
	void setAvailability(std::string);
	void setRemark(std::string);
	void setLoginCreate(int);
	void setLoginEdit(int);
	void setLoginAvailability(int);
	void setDateTimeCreate(QDateTime);
	void setDateTimeEdit(QDateTime);
	void setDateTimeAvailability(QDateTime);
	int getId();
	QDate getDate();
	Client getClient();
	std::string getPayment();
	QString getQPayment();
	std::string getAmount();
	QString getQAmount();
	Staff getManager();
	Staff getDesigner();
	std::vector<OrderPosition> getPositionsList();
	std::string getAvailability();
	QString getQAvailability();
	std::string getRemark();
	QString getQRemark();
	int getLoginCreate();
	int getLoginEdit();
	int getLoginAvailability();
	QDateTime getDateTimeCreate();
	QDateTime getDateTimeEdit();
	QDateTime getDateTimeAvailability();
};