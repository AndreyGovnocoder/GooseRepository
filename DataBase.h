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
#include <vector>
#include <qfile.h>
#include <qtextstream.h>

class DataBase
{
public:
    DataBase() = default;
    ~DataBase() = default;

    static const QString TABLE_ACCOUNTS;
    static const QString TABLE_CLIENTS;
    static const QString TABLE_STAFFS;
    static const QString TABLE_ORDERS;
    static const QString TABLE_POSITIONS;
    static const QString TABLE_RECEIPT_COUNT;

    static int getLastId(const QString&);
    static bool incrementReceiptCount();
    static int getReceiptCount();
    static std::vector<Client> getClientsList();
    static bool addClient(const Client&);
    static bool editClient(const Client&);
    static bool editClient(const Client*);
    static bool removeClient(int);
    static std::vector<Staff> getStaffList();
    static bool addStaff(const Staff&);
    static bool editStaff(const Staff&);
    static bool editStaff(const Staff*);
    static bool removeStaff(int);    
    static std::vector<Order> getOrdersList();
    static bool addOrder(const Order&);
    static bool editOrder(const Order*);
    static bool editOrder(const Order&);
    static bool removeOrder(int);
    static std::vector<OrderPosition> getOrderPositionsList(int);
    static std::vector<OrderPosition> getAllPositions();
    static bool addPosition(int, const OrderPosition&);
    static bool editPosition(const OrderPosition&);
    static bool removePositionById(int);
    static bool removePositionByIdOrder(int);
    static std::vector<StaffAccount> getAccountsList();
    static bool addAccount(const StaffAccount&);    
};

#endif  DATABASE_H