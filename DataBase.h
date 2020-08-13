#pragma once
#ifndef DATABASE_H
#define DATABASE_H
#include "Client.h"
#include "Staff.h"
#include "StaffLogin.h"
#include <qstring.h>
#include <vector>
#include "Order.h"

//#define DATABASE_NAME       "OrderBasePrint_dataBase.mdb"
//#define TABLE_CLIENTS                  "clients.txt"
//#define TABLE_STAFF                    "staff.txt"

class DataBase
{

public:
    DataBase();
    ~DataBase();

    void connectToDataBase();
    static std::vector<Client> getClientsList();
    static int getLastId(QString);
    static void addClient(Client*);
    static Client getClient(int);
    static void editClient(Client);
    static void removeClient(int);
    static void addStaff(Staff*);
    static Staff getStaff(int);
    static void removeStaff(int);
    static void editStaff(Staff);
    static void addOrder(Order*);
    static Order getOrder(int);
    static void removeOrder(int);
    static void editOrder(Order*);
    static QString getTableClients();
    static QString getTableStaff();
    static QString getTableOrders();
    static QString getTableOrderPositions();
    static QString getTableLogins();
    static std::vector<Staff> getStaffList();
    static std::vector<Order> getOrdersList();
    static std::vector<OrderPosition> getOrderPositionsList(int);
    static std::vector<OrderPosition> getAllPositions();
    static void setAvailabilityOrder(int, int);
    static void addLogin(StaffLogin*);
    static StaffLogin getLogin(int);
    static std::vector<StaffLogin> getLoginsList();

private:

    /*
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createDeviceTable();
    */
};

#endif  DATABASE_H