#pragma once

#include <QtWidgets/QMainWindow>
#include "Order.h"
#include "ui_MainForm.h"
#include "StaffAccount.h"
#include "DataBase.h"
#include <QtWidgets\qmessagebox.h>
#include "StaffsForm.h"
#include "AddClientForm.h"
#include "ClientsForm.h"
#include "LoginPassDialog.h"
#include "CreateOrderDialog.h"

class MainForm : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainFormClass ui;
    StaffAccount _account;
    void setPositionsTableWidget(const Order*);
    void setClientCard(int);
    void setRemark(int);
    void clearClientCard();
    void clearRemark();
    void setChangesOrderCard(int);
    void clearChangesOrderCard();
    /*static void setOrdersList(const std::vector<Order>& ordersList) { _ordersList = ordersList; };
    void setClientsList(const std::vector<Client>& clientsList) { _clientsList = clientsList; };
    void setStaffsList(const std::vector<Staff>& staffsList) { _staffsList = staffsList; };
    void setPositionsList(const std::vector<OrderPosition>& positionsList) { _positionsList = positionsList; };
    void setAccountsList(const std::vector<StaffAccount>& accountsList) { _accountsList = accountsList; };*/

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
    static std::vector<Order> _ordersList;
    static std::vector<Client> _clientsList;
    static std::vector<Staff> _staffsList;
    static std::vector<OrderPosition> _positionsList;
    static std::vector<StaffAccount> _accountsList;
    void setOrdersTableWidget();
    void setOrdersTableWidget(const std::vector<Order*>&);
    void clearPositionsTableWidget();
    void setTransparentClientCard();
    void setAccount(const StaffAccount& account) { _account = account; };
    const StaffAccount& getAccount() const { return _account; };
    Order* findOrder(int orderId);
    Client* findClient(int clientId);
    Staff* findStaff(int staffId);
    std::vector<OrderPosition> findOrderPositions(int orderId);
    StaffAccount* findAccount(int accountId);
    static int getIndex(const std::vector<Order>&, int);
    static int getIndex(const std::vector<Client>&, int);
    static int getIndex(const std::vector<Staff>&, int);
};
