#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include "Client.h"
#include "Staff.h"
#include "StaffAccount.h"
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

    static const QString TABLE_ACCOUNTS;
    static const QString TABLE_CLIENTS;
    static const QString TABLE_STAFFS;
    static const QString TABLE_ORDERS;
    static const QString TABLE_POSITIONS;

    static int getLastId(const QString&);
    static std::vector<Client> getClientsList();   
    static void addClient(const Client&);
    static Client getClient(int);
    static void editClient(const Client&);
    static void removeClient(int);
    static std::vector<Staff> getStaffList();
    static void addStaff(const Staff&);
    static Staff getStaff(int);
    static void removeStaff(int);
    static void editStaff(const Staff&);
    static std::vector<Order> getOrdersList();
    static bool addOrder(const Order&);
    static Order getOrder(int);
    static bool removeOrder(int);
    static bool editOrder(const Order*);
    static bool editOrder(const Order&);  
    static void addPosition(int, const OrderPosition&);
    static void editPosition(const OrderPosition&);
    static void removePositionById(int);
    static void removePositionByIdOrder(int);
    static std::vector<OrderPosition> getOrderPositionsList(int);
    static std::vector<OrderPosition> getAllPositions();
    static void addAccount(const StaffAccount&);
    static StaffAccount getAccount(int);
    static std::vector<StaffAccount> getAccountsList();

};

#endif  DATABASE_H