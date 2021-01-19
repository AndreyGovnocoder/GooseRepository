#pragma once
#include <string>
#include <qstring.h>

class OrderPosition 
{
public:
	OrderPosition() = default;
	~OrderPosition() = default;
	void setIdOrder(int idOrder) { _idOrder = idOrder; };
	void setIdPosition(int idPosition) { _idPosition = idPosition; };
	void setDescription(const std::string& description) { _description = description; };
	void setQuantity(const std::string& quantity) { _quantity = quantity; };
	void setIssue(const std::string& issue) { _issue = issue; };
	int getIdOrder() const { return _idOrder; };
	int getIdPosition() const { return _idPosition; };
	const std::string& getDescription() const { return _description; };
	const std::string& getQuantity() const { return _quantity; };
	const std::string& getIssue() const { return _issue; };

private:
	int _idOrder;
	int _idPosition;
	std::string _description;
	std::string _quantity;
	std::string _issue;
};
