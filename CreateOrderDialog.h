#pragma once

#include <QDialog>
#include "ui_CreateOrderDialog.h"
#include "OrderPosition.h"
#include "Order.h"
#include "StaffAccount.h"
#include "MainForm.h"
#include "SetDateDialog.h"
#include "Client.h"
#include "DataBase.h"
#include "qmessagebox.h"
#include <qcompleter.h>

class CreateOrderDialog : public QDialog, public Ui::CreateOrderDialog
{
	Q_OBJECT

public:
	CreateOrderDialog(QWidget* parent);
	CreateOrderDialog(QWidget* parent, Order* editOrder);
	~CreateOrderDialog() = default;
	Order* getEditOrder() { return _editOrder; };
	Order& getNewOrder() { return _newOrder; }
	void setPositionsList(const std::vector<OrderPosition>& positionsList);
	void setAccount(const StaffAccount* account) { _account = account; };
	const StaffAccount* getAccount() const { return _account; };
	bool _isOk = false;

private:
	const StaffAccount* _account;
	Order* _editOrder;
	Order _newOrder;
	void setCurrentDate();
	void setClientsList();
	void setPayment();
	void setManagersList();
	void setDesignersList();
	void setIssueComboBox();
	void addPosition();
	std::vector<OrderPosition> getPositionsList();
	std::string getRemark();
	void setEditOrder();
	void setEditOrderToUI();
	void setNewOrder();

private slots:
	void openCalendarSlot();
	void addOrderToDBSlot();
	void addPositionSlot();
	void removePositionSlot();
	void saveChangesSlot();
};