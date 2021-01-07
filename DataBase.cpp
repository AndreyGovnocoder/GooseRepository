#include "DataBase.h"
#include <vector>
#include <qfile.h>
#include <qtextstream.h>
#include <qstring.h>
#include <qmessagebox.h>

const QString DataBase::TABLE_ACCOUNTS("accounts");
const QString DataBase::TABLE_CLIENTS("clients");
const QString DataBase::TABLE_STAFFS("staffs");
const QString DataBase::TABLE_ORDERS("orders");
const QString DataBase::TABLE_POSITIONS("positions");

std::vector<Client> DataBase::getClientsList() 
{
    //получаем список клиентов из БД

    std::vector<Client> clientsList;

    QSqlQuery query("SELECT * FROM " + TABLE_CLIENTS);
    while (query.next())
    {
        Client client(
            query.value(0).toInt(), 
            query.value(1).toString().toStdString(), 
            query.value(2).toString().toStdString(), 
            query.value(3).toString().toStdString());
        clientsList.push_back(std::move(client));
    }

    return clientsList;
}

void DataBase::addClient(const Client& newClient) 
{
    //добавляем клиента в БД

    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_CLIENTS + " (name, phone, mail)"
        "VALUES (:name, :phone, :mail);");
    query.bindValue(":name", QString::fromStdString(newClient.getName()));
    query.bindValue(":phone", QString::fromStdString(newClient.getPhone()));
    query.bindValue(":mail", QString::fromStdString(newClient.getMail()));  
        
    if (!query.exec()) QMessageBox::warning(0, "", "error add client");

    //db.close();
}

Client DataBase::getClient(int clientId) 
{
    //получаем клиента по id

    Client client;

    QSqlQuery query("SELECT * FROM " + TABLE_CLIENTS + " WHERE _id=" + QString::number(clientId));
    
    while (query.next())
    {
        client.setId(clientId);
        client.setName(query.value(1).toString().toStdString());
        client.setPhone(query.value(2).toString().toStdString());
        client.setMail(query.value(3).toString().toStdString());
    }

    return client;
}

void DataBase::removeClient(int id) 
{
    //удаляем клиента из БД

    QSqlQuery query("DELETE FROM " + TABLE_CLIENTS + " WHERE _id=" + QString::number(id));

    if (!query.exec()) QMessageBox::warning(0, "", "remove client is unsuccessfully");
}

int DataBase::getLastId(const QString& table) 
{
    // получаем последний id в таблице БД

    int lastId;

    QSqlQuery query("SELECT _id FROM " + table);
   
    query.last();
    lastId = query.value(0).toInt();
    if(!query.exec()) QMessageBox::warning(0, "", "error get last id");

    return lastId;
}

void DataBase::editClient(const Client& client) 
{
    //редактируем клиента

    QSqlQuery query;
    query.prepare("UPDATE " + TABLE_CLIENTS + " SET name = ?, phone = ?, mail = ?  WHERE _id=" + QString::number(client.getId()));
    query.addBindValue(QString::fromStdString(client.getName()));
    query.addBindValue(QString::fromStdString(client.getPhone()));
    query.addBindValue(QString::fromStdString(client.getMail()));

    if (!query.exec()) QMessageBox::warning(0, "", "edit client is unsuccessfully");
}

std::vector<Staff> DataBase::getStaffList() 
{
    //получаем список сотрудников из БД

    std::vector<Staff> staffList;

    QSqlQuery query("SELECT * FROM " + TABLE_STAFFS);
    while (query.next())
    {
        Staff staff(
            query.value(0).toInt(),
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString());
        staffList.push_back(std::move(staff));
    }

    return staffList;
}

void DataBase::addStaff(const Staff& newStaff) 
{
    //добавляем сотрудника в БД


    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_STAFFS + " (name, position)"
        "VALUES (:name, :position);");
    query.bindValue(":name", QString::fromStdString(newStaff.getName()));
    query.bindValue(":position", QString::fromStdString(newStaff.getPosition()));

    if (!query.exec()) QMessageBox::warning(0, "", "error add staff");
}

Staff DataBase::getStaff(int staffId) 
{
    //получаем сотрудника по id

    Staff staff;

    QSqlQuery query("SELECT * FROM " + TABLE_STAFFS + " WHERE _id=" + QString::number(staffId));

    while (query.next())
    {
        staff.setId(staffId);
        staff.setName(query.value(1).toString().toStdString());
        staff.setPosition(query.value(2).toString().toStdString());
    }

    return staff;
}

void DataBase::removeStaff(int staffId) 
{
    //удаляем сотрудника из БД


    QSqlQuery query("DELETE FROM " + TABLE_STAFFS + " WHERE _id=" + QString::number(staffId));

    if (!query.exec()) QMessageBox::warning(0, "", "remove staff is unsuccessfully");
}

void DataBase::editStaff(const Staff& editStaff) 
{
    //редактируем сотрудника

    QSqlQuery query;
    query.prepare("UPDATE " + TABLE_STAFFS + " SET name = ?, position = ?  WHERE _id=" + QString::number(editStaff.getId()));
    query.addBindValue(QString::fromStdString(editStaff.getName()));
    query.addBindValue(QString::fromStdString(editStaff.getPosition()));

    if (!query.exec()) 
        QMessageBox::warning(0, "", "edit staff is unsuccessfully");
}

bool DataBase::addOrder(const Order& order) 
{
    //добавляем заказ в БД
    bool succeful = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_ORDERS + 
        " (date, client, amount, payment, manager, designer, availability, remark, loginCreate, loginEdit, loginAvailability, dateTimeCreate, dateTimeEdit, dateTimeAvailability)"
        " VALUES (:date, :client, :amount, :payment, :manager, :designer, :availability, :remark, :loginCreate, :loginEdit, :loginAvailability, :dateTimeCreate, :dateTimeEdit, :dateTimeAvailability);");
    query.bindValue(":date", order.getDate());
    query.bindValue(":client", order.getClient());
    query.bindValue(":amount", QString::fromStdString(order.getAmount()));
    query.bindValue(":payment", QString::fromStdString(order.getPayment()));
    query.bindValue(":manager", order.getManager());
    query.bindValue(":designer", order.getDesigner());
    query.bindValue(":availability", QString::fromStdString(order.getAvailability()));
    query.bindValue(":remark", QString::fromStdString(order.getRemark()));
    query.bindValue(":loginCreate", order.getAccountCreate());
    query.bindValue(":loginEdit", order.getAccountEdit());
    query.bindValue(":loginAvailability", order.getAccountAvailability());
    query.bindValue(":dateTimeCreate", order.getDateTimeCreate());
    query.bindValue(":dateTimeEdit", order.getDateTimeEdit());
    query.bindValue(":dateTimeAvailability", order.getDateTimeAvailability());

    if (query.exec())
        succeful = true;
    else
        return false;

    if (succeful)
    {
        size_t i = 0;
        for (; i < order.getPositionsList().size(); ++i)
        {
            DataBase::addPosition(DataBase::getLastId(TABLE_ORDERS), order.getPositionsList()[i]);
        }
        return true;
    }
    else
        return false;
}

Order DataBase::getOrder(int orderId) 
{
    //получаем заказ из БД по id

    Order order;

    QSqlQuery query("SELECT * FROM " + TABLE_ORDERS + " WHERE _id=" + QString::number(orderId));

    while (query.next())
    {
        order.setId(query.value(0).toInt());
        order.setDate(query.value(1).toDate());
        order.setClient(query.value(2).toInt());
        order.setAmount(query.value(3).toString().toStdString());
        order.setPayment(query.value(4).toString().toStdString());
        order.setManager(query.value(5).toInt());
        order.setDesigner(query.value(6).toInt());
        order.setAvailability(query.value(7).toString().toStdString());
        order.setRemark(query.value(8).toString().toStdString());
        order.setAccountCreate(query.value(9).toInt());
        order.setAccountEdit(query.value(10).toInt());
        order.setAccountAvailability(query.value(11).toInt());
        order.setDateTimeCreate(query.value(12).toDateTime());
        order.setDateTimeEdit(query.value(13).toDateTime());
        order.setDateTimeAvailability(query.value(14).toDateTime());
    }

    order.setPositionsList(DataBase::getOrderPositionsList(order.getId()));

    return order;
}

std::vector<Order> DataBase::getOrdersList() 
{
    //получаем список заказов

    std::vector<Order> ordersList;

    QSqlQuery query("SELECT * FROM " + TABLE_ORDERS);
    while (query.next())
    {
        Order order;
        order.setId(query.value(0).toInt());
        order.setDate(query.value(1).toDate());
        order.setClient(query.value(2).toInt());
        order.setAmount(query.value(3).toString().toStdString());
        order.setPayment(query.value(4).toString().toStdString());
        order.setManager(query.value(5).toInt());
        order.setDesigner(query.value(6).toInt());
        order.setAvailability(query.value(7).toString().toStdString());
        order.setRemark(query.value(8).toString().toStdString());
        order.setAccountCreate(query.value(9).toInt());
        order.setAccountEdit(query.value(10).toInt());
        order.setAccountAvailability(query.value(11).toInt());
        order.setDateTimeCreate(query.value(12).toDateTime());
        order.setDateTimeEdit(query.value(13).toDateTime());
        order.setDateTimeAvailability(query.value(14).toDateTime());
        order.setPositionsList(getOrderPositionsList(order.getId()));
        ordersList.push_back(std::move(order));
    }

    return ordersList;
}

void DataBase::addPosition(int orderId, const OrderPosition& position)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_POSITIONS + " (idOrder, description, quantity, issue)"
        " VALUES (:idOrder, :description, :quantity, :issue);");

    query.bindValue(":idOrder", orderId);
    query.bindValue(":description", QString::fromStdString(position.getDescription()));
    query.bindValue(":quantity", QString::fromStdString(position.getQuantity()));
    query.bindValue(":issue", QString::fromStdString(position.getIssue()));
    if (!query.exec()) QMessageBox::warning(0, "", "error add position");
}

void DataBase::editPosition(const OrderPosition& editPosition) 
{
    QSqlQuery query;
    query.prepare("UPDATE " + TABLE_POSITIONS +
        " SET description=?, quantity=?, issue=?"
        "  WHERE _id=" + QString::number(editPosition.getIdPosition()));
    query.addBindValue(QString::fromStdString(editPosition.getDescription()));
    query.addBindValue(QString::fromStdString(editPosition.getQuantity()));
    query.addBindValue(QString::fromStdString(editPosition.getIssue()));

    if (!query.exec()) QMessageBox::warning(0, "", "error add position");
}

void DataBase::removePositionById(int idPosition)
{
    QSqlQuery query("DELETE FROM " + TABLE_POSITIONS + " WHERE _id=" + QString::number(idPosition));

    if (!query.exec()) QMessageBox::warning(0, "", "remove position is unsuccessfully");
}

void DataBase::removePositionByIdOrder(int idOrder)
{

    QSqlQuery query("DELETE FROM " + TABLE_POSITIONS + " WHERE idOrder=" + QString::number(idOrder));

    if (!query.exec()) QMessageBox::warning(0, "", "remove position is unsuccessfully");
}

std::vector<OrderPosition> DataBase::getOrderPositionsList(int orderId) 
{
    //получаем список позиций по id заказа

    std::vector<OrderPosition> positionsList;

    QSqlQuery query("SELECT * FROM " + TABLE_POSITIONS + " WHERE idOrder=" + QString::number(orderId));
    while (query.next())
    {
        OrderPosition position;
        position.setIdPosition(query.value(0).toInt());
        position.setIdOrder(query.value(1).toInt());
        position.setDescription(query.value(2).toString().toStdString());
        position.setQuantity(query.value(3).toString().toStdString());
        position.setIssue(query.value(4).toString().toStdString());

        positionsList.push_back(std::move(position));
    }

    return positionsList;
}

std::vector<OrderPosition> DataBase::getAllPositions() 
{
    //получаем список позиций всех заказов

    std::vector<OrderPosition> positionsList;

    QSqlQuery query("SELECT * FROM " + TABLE_POSITIONS);
    while (query.next())
    {
        OrderPosition position; 
        position.setIdPosition(query.value(0).toInt());
        position.setIdOrder(query.value(1).toInt());
        position.setDescription(query.value(2).toString().toStdString());
        position.setQuantity(query.value(3).toString().toStdString());
        position.setIssue(query.value(4).toString().toStdString());
            
        positionsList.push_back(std::move(position));
    }

    return positionsList;
}

bool DataBase::removeOrder(int orderId) 
{
    //удаляем Заказ из БД

    QSqlQuery query("DELETE FROM " + TABLE_ORDERS + " WHERE _id=" + QString::number(orderId));

    if (!query.exec())
    {
        QMessageBox::warning(0, "", "remove order is unsuccessfully");
        return false;
    }        
    else
    {
        DataBase::removePositionByIdOrder(orderId);
        return true;
    }
}

bool DataBase::editOrder(const Order& editOrder) 
{
    //редактируем заказ
    bool succeful = false;
    QSqlQuery query;
    query.prepare("UPDATE " + TABLE_ORDERS +
        " SET date=?, client=?, amount=?, payment=?, manager=?, designer=?, availability=?, remark=?, loginCreate=?, loginEdit=?, loginAvailability=?, dateTimeCreate=?, dateTimeEdit=?, dateTimeAvailability=?"
        "  WHERE _id=" + QString::number(editOrder.getId()));
    query.addBindValue(editOrder.getDate());
    query.addBindValue(editOrder.getClient());
    query.addBindValue(QString::fromStdString(editOrder.getAmount()));
    query.addBindValue(QString::fromStdString(editOrder.getPayment()));
    query.addBindValue(editOrder.getManager());
    query.addBindValue(editOrder.getDesigner());
    query.addBindValue(QString::fromStdString(editOrder.getAvailability()));
    query.addBindValue(QString::fromStdString(editOrder.getRemark()));
    query.addBindValue(editOrder.getAccountCreate());
    query.addBindValue(editOrder.getAccountEdit());
    query.addBindValue(editOrder.getAccountAvailability());
    query.addBindValue(editOrder.getDateTimeCreate());
    query.addBindValue(editOrder.getDateTimeEdit());
    query.addBindValue(editOrder.getDateTimeAvailability());

    if (query.exec())
        succeful = true;
    else
        return false;

    if (succeful)
    {
        DataBase::removePositionByIdOrder(editOrder.getId());

        size_t i = 0;
        for (; i < editOrder.getPositionsList().size(); ++i)
        {
            DataBase::addPosition(editOrder.getId(), editOrder.getPositionsList()[i]);
        }

        return true;
    }
    else
        return false;
}

bool DataBase::editOrder(const Order* editOrder)
{
    //редактируем заказ
    bool succeful = false;
    QSqlQuery query;
    query.prepare("UPDATE " + TABLE_ORDERS +
        " SET date=?, client=?, amount=?, payment=?, manager=?, designer=?, availability=?, remark=?, loginCreate=?, loginEdit=?, loginAvailability=?, dateTimeCreate=?, dateTimeEdit=?, dateTimeAvailability=?"
        "  WHERE _id=" + QString::number(editOrder->getId()));
    query.addBindValue(editOrder->getDate());
    query.addBindValue(editOrder->getClient());
    query.addBindValue(QString::fromStdString(editOrder->getAmount()));
    query.addBindValue(QString::fromStdString(editOrder->getPayment()));
    query.addBindValue(editOrder->getManager());
    query.addBindValue(editOrder->getDesigner());
    query.addBindValue(QString::fromStdString(editOrder->getAvailability()));
    query.addBindValue(QString::fromStdString(editOrder->getRemark()));
    query.addBindValue(editOrder->getAccountCreate());
    query.addBindValue(editOrder->getAccountEdit());
    query.addBindValue(editOrder->getAccountAvailability());
    query.addBindValue(editOrder->getDateTimeCreate());
    query.addBindValue(editOrder->getDateTimeEdit());
    query.addBindValue(editOrder->getDateTimeAvailability());

    if (query.exec())
        succeful = true;
    else
        return false;

    if (succeful)
    {
        DataBase::removePositionByIdOrder(editOrder->getId());

        size_t i = 0;
        for (; i < editOrder->getPositionsList().size(); ++i)
        {
            DataBase::addPosition(editOrder->getId(), editOrder->getPositionsList()[i]);
        }

        return true;
    }
    else
        return false;
}

void DataBase::addAccount(const StaffAccount& account) 
{
    //сохраняем логин в БД

    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_ACCOUNTS + " (name, position, login, password)"
        "VALUES (:name, :position, :login, :password);");
    query.bindValue(":name", QString::fromStdString(account.getName()));
    query.bindValue(":position", QString::fromStdString(account.getPosition()));
    query.bindValue(":login", QString::fromStdString(account.getLogin()));
    query.bindValue(":password", QString::fromStdString(account.getPassword()));

    if (!query.exec()) QMessageBox::warning(0, "", "error add account ");
  
}

StaffAccount DataBase::getAccount(int accountId) 
{
    //получаем логин из БД

    StaffAccount account;

    QSqlQuery query("SELECT * FROM " + TABLE_ACCOUNTS + " WHERE _id=" + QString::number(accountId));

    while (query.next())
    {
        account.setId(accountId);
        account.setName(query.value(1).toString().toStdString());
        account.setPosition(query.value(2).toString().toStdString());
        account.setLogin(query.value(3).toString().toStdString());
        account.setPassword(query.value(4).toString().toStdString());
    }

    return account;
}

std::vector<StaffAccount> DataBase::getAccountsList() 
{
    std::vector<StaffAccount> accountsList;

    QSqlQuery query("SELECT * FROM " + TABLE_ACCOUNTS);
    while (query.next())
    {
        StaffAccount account;
        account.setId(query.value(0).toInt());
        account.setName(query.value(1).toString().toStdString());
        account.setPosition(query.value(2).toString().toStdString());
        account.setLogin(query.value(3).toString().toStdString());
        account.setPassword(query.value(4).toString().toStdString());
        accountsList.push_back(std::move(account));
    }

    return accountsList;
}