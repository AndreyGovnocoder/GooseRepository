#pragma once

#include <QtWidgets/QMainWindow>
#include "Order.h"
#include "ui_MainForm.h"
#include "StaffAccount.h"
#include "DataBase.h"
#include <QtWidgets\qmessagebox.h>
#include "StaffsFormDialog.h"
#include "LoginPassDialog.h"
#include "CreateOrderDialog.h"
#include "ClientsFormDialog.h"
#include "PrintReceiptDialog.h"

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(int accountId, QWidget* parent = Q_NULLPTR);
    ~MainForm() = default;
    static std::vector<Order> _ordersList;
    static std::vector<Client> _clientsList;
    static std::vector<Staff> _staffsList;
    static std::vector<OrderPosition> _positionsList;
    static std::vector<StaffAccount> _accountsList;
    void setOrdersTableWidget();
    void setOrdersTableWidget(const std::vector<Order*>&);
    void clearPositionsTableWidget();
    void setTransparentClientCard();
    static Order* findOrder(int orderId);
    static Client* findClient(int clientId);
    static Staff* findStaff(int staffId);
    static StaffAccount* findAccount(int accountId);
    std::vector<OrderPosition*> findOrderPositions(int orderId);
    static OrderPosition* findPosition(int positionId);
    static bool checkStaffInOrders(int);
    static bool checkClientInOrders(int);

private:
    Ui::MainFormClass ui;
    StaffAccount* _currentAccount;
    std::vector<Order*> _foundOrders;
    void setPositionsTableWidget(const Order*);
    void setClientCard(int);
    void setRemark(int);
    void setChangesOrderCard(int);
    void clearClientCard();
    void clearRemark();    
    void clearChangesOrderCard();

private slots:
    void clientListSlot();
    void staffListSlot();
    void createOrderSlot();
    void editOrderSlot();
    void removeOrderSlot();
    void printOrderSlot();
    void clickOnRowSlot();
    void searchOnClientSlot();
    void slotCustomMenuRequested(const QPoint&);
    void slotSetAvailability();
};