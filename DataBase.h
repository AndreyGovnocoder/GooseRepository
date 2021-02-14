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

    static const QString DB_NAME;
    static const QString TABLE_ACCOUNTS;
    static const QString TABLE_CLIENTS;
    static const QString TABLE_STAFFS;
    static const QString TABLE_ORDERS;
    static const QString TABLE_POSITIONS;
    static const QString TABLE_RECEIPT_COUNT;

    static QSqlDatabase getDatabase() { return QSqlDatabase::database(DB_NAME); }
    static bool initDatabase();
    static int getLastId(const QString& table);
    static bool incrementReceiptCount();
    static int getReceiptCount();
    static std::vector<Client> getClientsList();
    static bool addClient(const Client& newClient);
    static bool editClient(const Client& client);
    static bool editClient(const Client* client);
    static bool removeClient(int clientId);
    static std::vector<Staff> getStaffList();
    static bool addStaff(const Staff&);
    static bool editStaff(const Staff&);
    static bool editStaff(const Staff*);
    static bool removeStaff(int staffId);    
    static std::vector<Order> getOrdersList();
    static bool addOrder(const Order&);
    static bool editOrder(const Order*);
    static bool editOrder(const Order&);
    static bool removeOrder(int orderId);
    static std::vector<OrderPosition> getOrderPositionsList(int);
    static std::vector<OrderPosition> getAllPositions();
    static bool addPosition(int orderId, const OrderPosition& position);
    static bool editPosition(const OrderPosition& editPosition);
    static bool removePositionById(int idPosition);
    static bool removePositionByIdOrder(int idOrder);
    static std::vector<StaffAccount> getAccountsList();
    static bool addAccount(const StaffAccount& newAccount);
};

#endif  DATABASE_H