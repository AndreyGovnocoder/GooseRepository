#pragma once

#include <QtWidgets/QMainWindow>
#include "Order.h"
#include "ui_MainForm.h"
#include "StaffLogin.h"

class MainForm : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainFormClass ui;
    StaffLogin _login;
    void setPositionsTableWidget(int);
    void setClientCard(int);
    void setRemark(int);
    void clearClientCard();
    void clearRemark();
    void setChangesOrderCard(int);
    void clearChangesOrderCard();

private slots:
    void addClientSlot();
    void clientListSlot();
    void staffListSlot();
    void createOrderSlot();
    void printOrderSlot();
    void editOrderSlot();
    void removeOrderSlot();
    void clickOnRowSlot();
    void searchOnClientSlot();
    void slotCustomMenuRequested(const QPoint&);
    void slotSetAvailability();

public:
    MainForm(QWidget *parent = Q_NULLPTR);
    ~MainForm() = default;
    void setOrdersTableWidget(const std::vector<Order>&);
    void clearPositionsTableWidget();
    void setTransparentClientCard();
    void setLogin(const StaffLogin& login) { _login = login; };
    const StaffLogin& getLogin() const { return _login; };
};
