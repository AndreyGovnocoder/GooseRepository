#pragma once

#include <QDialog>
#include "ui_CreateOrderDialog.h"
#include "OrderPosition.h"
#include "Order.h"
#include "StaffLogin.h"
#include "MainForm.h"

class CreateOrderDialog : public QDialog, public Ui::CreateOrderDialog
{
	Q_OBJECT

private:
	StaffLogin _login;
	int _idEditOrder;
	void setCurrentDate();
	void setClientsList();
	void setPayment();
	void setManagersList();
	void setDesignersList();
	void setIssueComboBox();
	void addPosition();
	std::vector<OrderPosition> getPositionsList();
	std::string getRemark();
	Order getOrder();

private slots:
	void openCalendarSlot();
	void addOrderToDBSlot();
	void addPositionSlot();
	void removePositionSlot();
	void saveChangesSlot();

public:
	CreateOrderDialog(QWidget* parent);
	~CreateOrderDialog() = default;
	void setPositionsList(const std::vector<OrderPosition>&);
	void setIdEditOrder(int idEditOrder) { _idEditOrder = idEditOrder; };
	void setLogin(const StaffLogin& login)  { _login = login; };
	const StaffLogin& getLogin() const { return _login; };
};