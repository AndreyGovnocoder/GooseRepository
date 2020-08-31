#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QFile>
#include <QDate>
#include <QDebug>
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

public:
    DataBase() = default;
    ~DataBase() = default;

    static int getLastId(const QString&);
    static std::vector<Client> getClientsList();   
    static void addClient(const Client&);
    static Client getClient(const int);
    static void editClient(const Client&);
    static void removeClient(const int);
    static std::vector<Staff> getStaffList();
    static void addStaff(const Staff&);
    static Staff getStaff(int);
    static void removeStaff(int);
    static void editStaff(const Staff&);
    static std::vector<Order> getOrdersList();
    static void addOrder(const Order&);
    static Order getOrder(const int);
    static void removeOrder(const int);
    static void editOrder(const Order&);
    static QString getTableClients() { return "clients"; };
    static QString getTableStaff() { return "staffs"; };
    static QString getTableOrders() { return "orders"; };
    static QString getTableOrderPositions() { return "positions"; };
    static QString getTableLogins() { return "logins"; };   
    static void addPosition(int, const OrderPosition&);
    static void editPosition(const OrderPosition&);
    static void removePositionById(const int);
    static void removePositionByIdOrder(const int);
    static std::vector<OrderPosition> getOrderPositionsList(int);
    static std::vector<OrderPosition> getAllPositions();
    static void setAvailabilityOrder(int, int);
    static void addLogin(const StaffLogin&);
    static StaffLogin getLogin(int);
    static std::vector<StaffLogin> getLoginsList();

};

#endif  DATABASE_H