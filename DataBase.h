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
private:

    /*
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createDeviceTable();
    */

public:
    DataBase() = default;
    ~DataBase() = default;

    void connectToDataBase();
    static std::vector<Client> getClientsList();
    static int getLastId(const QString&);
    static void addClient(const Client&);
    static Client getClient(int);
    static void editClient(const Client&);
    static void removeClient(int);
    static void addStaff(const Staff&);
    static Staff getStaff(int);
    static void removeStaff(int);
    static void editStaff(const Staff&);
    static void addOrder(const Order&);
    static Order getOrder(int);
    static void removeOrder(int);
    static void editOrder(const Order&);
    static QString getTableClients() { return "clients.txt"; };
    static QString getTableStaff() { return "staff.txt"; };
    static QString getTableOrders() { return "orders.txt"; };
    static QString getTableOrderPositions() { return "positions.txt"; };
    static QString getTableLogins() { return "logins"; };
    static std::vector<Staff> getStaffList();
    static std::vector<Order> getOrdersList();
    static std::vector<OrderPosition> getOrderPositionsList(int);
    static std::vector<OrderPosition> getAllPositions();
    static void setAvailabilityOrder(int, int);
    static void addLogin(const StaffLogin&);
    static StaffLogin getLogin(int);
    static std::vector<StaffLogin> getLoginsList();

};

#endif  DATABASE_H