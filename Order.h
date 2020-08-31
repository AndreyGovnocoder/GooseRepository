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
	Client _client;
	std::string _payment;
	std::string _amount;
	Staff _manager;
	Staff _designer;
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
	void setClient(const Client& client) { _client = client; };
	void setPayment(const std::string& payment) { _payment = payment; };
	void setAmount(const std::string& amount) { _amount = amount; };
	void setManager(const Staff& manager) { _manager = manager; };
	void setDesigner(const Staff& designer) { _designer = designer; };
	void setPositionsList(const std::vector<OrderPosition> positionsList) { _positionsList = positionsList; };
	void setAvailability(const std::string& availability) { _availability = availability; };
	void setRemark(const std::string& remark) { _remark = remark; };
	void setLoginCreate(int loginCreate) { _loginCreate = loginCreate; };
	void setLoginEdit(int loginEdit) { _loginEdit = loginEdit; };
	void setLoginAvailability(int loginAvailability) { _loginAvailability = loginAvailability; };
	void setDateTimeCreate(const QDateTime& dateTimeCreate){ _dateTimeCreate = dateTimeCreate; };
	void setDateTimeEdit(const QDateTime& dateTimeEdit) { _dateTimeEdit = dateTimeEdit; };
	void setDateTimeAvailability(const QDateTime& dateTimeAvailability) { _dateTimeAvailability = dateTimeAvailability; };
	int getId()  const { return _id; };
	const QDate& getDate() const { return _date; };
	const Client& getClient() const { return _client; };
	const std::string& getPayment() const { return _payment; };
	const std::string& getAmount() const { return _amount; };
	const Staff& getManager() const { return _manager; };
	const Staff& getDesigner() const { return _designer; };
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