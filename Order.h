#pragma once
#include <string>
#include <qdatetime.h>
#include <qstring.h>
#include "Client.h"
#include "Staff.h"
#include "OrderPosition.h"

class Order
{
private:
	int _id;
	QDate _date;
	int _clientId;
	std::string _payment;
	std::string _amount;
	int _managerId;
	int _designerId;
	std::vector<OrderPosition> _positionsList;
	std::string _availability;
	std::string _remark;
	int _loginCreate;
	int _loginEdit;
	int _loginAvailability;
	QDateTime _dateTimeCreate;
	QDateTime _dateTimeEdit;
	QDateTime _dateTimeAvailability;

public:
	Order() = default;
	~Order() = default;
	void setId(int id) { _id = id; };
	void setDate(const QDate& date) { _date = date; };
	void setClient(const int clientId) { _clientId = clientId; };
	void setPayment(const std::string& payment) { _payment = payment; };
	void setAmount(const std::string& amount) { _amount = amount; };
	void setManager(int managerId) { _managerId = managerId; };
	void setDesigner(int designerId) { _designerId = designerId; };
	void setPositionsList(const std::vector<OrderPosition> positionsList) { _positionsList = positionsList; };
	void setAvailability(const std::string& availability) { _availability = availability; };
	void setRemark(const std::string& remark) { _remark = remark; };
	void setLoginCreate(const int loginCreate) { _loginCreate = loginCreate; };
	void setLoginEdit(const int loginEdit) { _loginEdit = loginEdit; };
	void setLoginAvailability(const int loginAvailability) { _loginAvailability = loginAvailability; };
	void setDateTimeCreate(const QDateTime& dateTimeCreate){ _dateTimeCreate = dateTimeCreate; };
	void setDateTimeEdit(const QDateTime& dateTimeEdit) { _dateTimeEdit = dateTimeEdit; };
	void setDateTimeAvailability(const QDateTime& dateTimeAvailability) { _dateTimeAvailability = dateTimeAvailability; };
	int getId()  const { return _id; };
	const QDate& getDate() const { return _date; };
	int getClient() const { return _clientId; };
	const std::string& getPayment() const { return _payment; };
	const std::string& getAmount() const { return _amount; };
	int getManager() const { return _managerId; };
	int getDesigner() const { return _designerId; };
	const std::vector<OrderPosition>& getPositionsList() const { return _positionsList; };
	const std::string& getAvailability() const { return _availability; };
	const std::string& getRemark() const { return _remark; };
	int getLoginCreate() const { return _loginCreate; };
	int getLoginEdit() const { return _loginEdit; };
	int getLoginAvailability() const { return _loginAvailability; };
	const QDateTime& getDateTimeCreate() const { return _dateTimeCreate; };
	const QDateTime& getDateTimeEdit() const { return _dateTimeEdit; };
	const QDateTime& getDateTimeAvailability() const { return _dateTimeAvailability; };
};