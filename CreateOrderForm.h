#pragma once

#include <QWidget>
#include "ui_CreateOrderForm.h"
#include "OrderPosition.h"
#include "Order.h"
#include "StaffLogin.h"

class CreateOrderForm : public QWidget, public Ui::CreateOrderForm
{
	Q_OBJECT

public:
	CreateOrderForm(QTableWidget*, QTableWidget*, StaffLogin, QWidget* parent = Q_NULLPTR);
	~CreateOrderForm();
	void setPositionsList(std::vector<OrderPosition>);
	void setIdEditOrder(int);
	void setLogin(StaffLogin);
	StaffLogin getLogin();

private slots:

	void slot1();
	void slot2();
	void slot3();
	void slot4();
	void slot5();

private:
	QTableWidget* ordersTableWidget;
	QTableWidget* positionsTableWidget;
	StaffLogin login;
	int idEditOrder;
	void setCurrentDate();
	void setClientsList();
	void setPayment();
	void setManagersList();
	void setDesignersList();
	void setIssueComboBox();
	void addPosition();
	std::vector<OrderPosition> getPositionsList();
	QString getRemark();
	Order getOrder();
};
