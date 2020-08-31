#include "DataBase.h"
#include <vector>
#include <qfile.h>
#include <qtextstream.h>
#include <qstring.h>
#include <qmessagebox.h>


std::vector<Client> DataBase::getClientsList() 
{
    //получаем список клиентов из БД

    std::vector<Client> clientsList;
    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableClients());
    while (query.next())
    {
        Client client(
            query.value(0).toInt(), 
            query.value(1).toString().toStdString(), 
            query.value(2).toString().toStdString(), 
            query.value(3).toString().toStdString());
        clientsList.push_back(client);
    }

    db.close();

    return clientsList;
}

void DataBase::addClient(const Client& newClient) 
{
    //добавляем клиента в БД
    
    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("INSERT INTO " + DataBase::getTableClients() + " (name, phone, mail)"
        "VALUES (:name, :phone, :mail);");
    query.bindValue(":name", QString::fromStdString(newClient.getName()));
    query.bindValue(":phone", QString::fromStdString(newClient.getPhone()));
    query.bindValue(":mail", QString::fromStdString(newClient.getMail()));  
        
    if (!query.exec()) QMessageBox::warning(0, "", "error add client");

    db.close();
}

Client DataBase::getClient(const int clientId) 
{
    //получаем клиента по id

    Client client;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableClients() + " WHERE _id=" + QString::number(clientId));
    
    while (query.next())
    {
        client.setId(clientId);
        client.setName(query.value(1).toString().toStdString());
        client.setPhone(query.value(2).toString().toStdString());
        client.setMail(query.value(3).toString().toStdString());
    }
    db.close();

    return client;
}

void DataBase::removeClient(const int id) 
{
    //удаляем клиента из БД

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("DELETE FROM " + DataBase::getTableClients() + " WHERE _id=" + QString::number(id));

    if (!query.exec()) QMessageBox::warning(0, "", "remove client is unsuccessfully");

    db.close();
}

int DataBase::getLastId(const QString& table) 
{
    // получаем последний id в таблице БД

    int lastId;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT _id FROM " + table);
   
    query.last();
    lastId = query.value(0).toInt();
    if(!query.exec()) QMessageBox::warning(0, "", "error get last id");

    db.close();

    return lastId;
}

void DataBase::editClient(const Client& client) 
{
    //редактируем клиента

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("UPDATE " + DataBase::getTableClients() + " SET name = ?, phone = ?, mail = ?  WHERE _id=" + QString::number(client.getId()));
    query.addBindValue(QString::fromStdString(client.getName()));
    query.addBindValue(QString::fromStdString(client.getPhone()));
    query.addBindValue(QString::fromStdString(client.getMail()));

    if (!query.exec()) QMessageBox::warning(0, "", "edit client is unsuccessfully");

    db.close();
}

std::vector<Staff> DataBase::getStaffList() 
{
    //получаем список сотрудников из БД

    std::vector<Staff> staffList;
    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableStaff());
    while (query.next())
    {
        Staff staff(
            query.value(0).toInt(),
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString());
        staffList.push_back(staff);
    }

    db.close();

    return staffList;
}

void DataBase::addStaff(const Staff& newStaff) 
{
    //добавляем сотрудника в БД

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("INSERT INTO " + DataBase::getTableStaff() + " (name, position)"
        "VALUES (:name, :position);");
    query.bindValue(":name", QString::fromStdString(newStaff.getName()));
    query.bindValue(":position", QString::fromStdString(newStaff.getPosition()));

    if (!query.exec()) QMessageBox::warning(0, "", "error add staff");

    db.close();
}

Staff DataBase::getStaff(int staffId) 
{
    //получаем сотрудника по id

    Staff staff;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableStaff() + " WHERE _id=" + QString::number(staffId));

    while (query.next())
    {
        staff.setId(staffId);
        staff.setName(query.value(1).toString().toStdString());
        staff.setPosition(query.value(2).toString().toStdString());
    }

    db.close();

    return staff;
}

void DataBase::removeStaff(int staffId) 
{
    //удаляем сотрудника из БД

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("DELETE FROM " + DataBase::getTableStaff() + " WHERE _id=" + QString::number(staffId));

    if (!query.exec()) QMessageBox::warning(0, "", "remove staff is unsuccessfully");

    db.close();
}

void DataBase::editStaff(const Staff& editStaff) 
{
    //редактируем сотрудника

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("UPDATE " + DataBase::getTableStaff() + " SET name = ?, position = ?  WHERE _id=" + QString::number(editStaff.getId()));
    query.addBindValue(QString::fromStdString(editStaff.getName()));
    query.addBindValue(QString::fromStdString(editStaff.getPosition()));

    if (!query.exec()) QMessageBox::warning(0, "", "edit staff is unsuccessfully");

    db.close();
}

void DataBase::addOrder(const Order& order) 
{
    //добавляем заказ в БД

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("INSERT INTO " + DataBase::getTableOrders() + 
        " (date, client, amount, payment, manager, designer, availability, remark, loginCreate, loginEdit, loginAvailability, dateTimeCreate, dateTimeEdit, dateTimeAvailability)"
        " VALUES (:date, :client, :amount, :payment, :manager, :designer, :availability, :remark, :loginCreate, :loginEdit, :loginAvailability, :dateTimeCreate, :dateTimeEdit, :dateTimeAvailability);");
    query.bindValue(":date", order.getDate().toString("dd.MM.yyyy"));
    query.bindValue(":client", order.getClient());
    query.bindValue(":amount", QString::fromStdString(order.getAmount()));
    query.bindValue(":payment", QString::fromStdString(order.getPayment()));
    query.bindValue(":manager", order.getManager());
    query.bindValue(":designer", order.getDesigner());
    query.bindValue(":availability", QString::fromStdString(order.getAvailability()));
    query.bindValue(":remark", QString::fromStdString(order.getRemark()));
    query.bindValue(":loginCreate", order.getLoginCreate());
    query.bindValue(":loginEdit", order.getLoginEdit());
    query.bindValue(":loginAvailability", order.getLoginAvailability());
    query.bindValue(":dateTimeCreate", order.getDateTimeCreate().toString("dd.MM.yyyy hh:mm"));
    query.bindValue(":dateTimeEdit", order.getDateTimeEdit().toString("dd.MM.yyyy hh:mm"));
    query.bindValue(":dateTimeAvailability", order.getDateTimeAvailability().toString("dd.MM.yyyy hh:mm"));

    if (!query.exec()) QMessageBox::warning(0, "", "error add order");

    db.close();

    for (int i = 0; i < order.getPositionsList().size(); ++i)
    {
        DataBase::addPosition(DataBase::getLastId(DataBase::getTableOrders()), order.getPositionsList()[i]);
    }    
}

Order DataBase::getOrder(const int orderId) 
{
    //получаем заказ из БД по id

    Order order;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableOrders() + " WHERE _id=" + QString::number(orderId));

    while (query.next())
    {
        order.setId(query.value(0).toInt());
        QDate date = QDate::fromString(query.value(1).toString(), "dd.MM.yyyy");
        order.setDate(date);
        order.setClient(query.value(2).toInt());
        order.setAmount(query.value(3).toString().toStdString());
        order.setPayment(query.value(4).toString().toStdString());
        order.setManager(query.value(5).toInt());
        order.setDesigner(query.value(6).toInt());
        order.setAvailability(query.value(7).toString().toStdString());
        order.setRemark(query.value(8).toString().toStdString());
        order.setLoginCreate(query.value(9).toInt());
        order.setLoginEdit(query.value(10).toInt());
        order.setLoginAvailability(query.value(11).toInt());
        QDateTime dateTime = QDateTime::fromString(query.value(12).toString(), "dd.MM.yyyy hh:mm");
        order.setDateTimeCreate(dateTime);
        dateTime = QDateTime::fromString(query.value(13).toString(), "dd.MM.yyyy hh:mm");
        order.setDateTimeEdit(dateTime);
        dateTime = QDateTime::fromString(query.value(14).toString(), "dd.MM.yyyy hh:mm");
        order.setDateTimeAvailability(dateTime);
    }

    db.close();

    order.setPositionsList(DataBase::getOrderPositionsList(order.getId()));

    return order;
}

std::vector<Order> DataBase::getOrdersList() 
{
    //получаем список заказов

    std::vector<Order> ordersList;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableOrders());
    while (query.next())
    {
        Order order;
        order.setId(query.value(0).toInt());
        QDate date = QDate::fromString(query.value(1).toString(), "dd.MM.yyyy");
        order.setDate(date);
        order.setClient(query.value(2).toInt());
        order.setAmount(query.value(3).toString().toStdString());
        order.setPayment(query.value(4).toString().toStdString());
        order.setManager(query.value(5).toInt());
        order.setDesigner(query.value(6).toInt());
        order.setAvailability(query.value(7).toString().toStdString());
        order.setRemark(query.value(8).toString().toStdString());
        order.setLoginCreate(query.value(9).toInt());
        order.setLoginEdit(query.value(10).toInt());
        order.setLoginAvailability(query.value(11).toInt());
        QDateTime dateTime = QDateTime::fromString(query.value(12).toString(), "dd.MM.yyyy hh:mm");
        order.setDateTimeCreate(dateTime);
        dateTime = QDateTime::fromString(query.value(13).toString(), "dd.MM.yyyy hh:mm");
        order.setDateTimeEdit(dateTime);
        dateTime = QDateTime::fromString(query.value(14).toString(), "dd.MM.yyyy hh:mm");
        order.setDateTimeAvailability(dateTime);

        ordersList.push_back(order);
    }

    db.close();

    return ordersList;
}

void DataBase::addPosition(int orderId, const OrderPosition& position)
{
    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("INSERT INTO " + DataBase::getTableOrderPositions() + " (idOrder, description, quantity, issue)"
        " VALUES (:idOrder, :description, :quantity, :issue);");

    query.bindValue(":idOrder", orderId);
    query.bindValue(":description", QString::fromStdString(position.getDescription()));
    query.bindValue(":quantity", QString::fromStdString(position.getQuantity()));
    query.bindValue(":issue", QString::fromStdString(position.getIssue()));
    if (!query.exec()) QMessageBox::warning(0, "", "error add position");

    db.close();
}

void DataBase::editPosition(const OrderPosition& editPosition) 
{
    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("UPDATE " + DataBase::getTableOrderPositions() +
        " SET description=?, quantity=?, issue=?"
        "  WHERE _id=" + QString::number(editPosition.getIdPosition()));
    query.addBindValue(QString::fromStdString(editPosition.getDescription()));
    query.addBindValue(QString::fromStdString(editPosition.getQuantity()));
    query.addBindValue(QString::fromStdString(editPosition.getIssue()));

    if (!query.exec()) QMessageBox::warning(0, "", "error add position");

    db.close();
}

void DataBase::removePositionById(const int idPosition)
{
    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("DELETE FROM " + DataBase::getTableOrderPositions() + " WHERE _id=" + QString::number(idPosition));

    if (!query.exec()) QMessageBox::warning(0, "", "remove position is unsuccessfully");

    db.close();
}

void DataBase::removePositionByIdOrder(const int idOrder)
{
    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("DELETE FROM " + DataBase::getTableOrderPositions() + " WHERE idOrder=" + QString::number(idOrder));

    if (!query.exec()) QMessageBox::warning(0, "", "remove position is unsuccessfully");

    db.close();
}

std::vector<OrderPosition> DataBase::getOrderPositionsList(int orderId) 
{
    //получаем список позиций по id заказа

    std::vector<OrderPosition> positionsList;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableOrderPositions() + " WHERE idOrder=" + QString::number(orderId));
    while (query.next())
    {
        OrderPosition position;
        position.setIdPosition(query.value(0).toInt());
        position.setIdOrder(query.value(1).toInt());
        position.setDescription(query.value(2).toString().toStdString());
        position.setQuantity(query.value(3).toString().toStdString());
        position.setIssue(query.value(4).toString().toStdString());

        positionsList.push_back(position);
    }

    return positionsList;
}

std::vector<OrderPosition> DataBase::getAllPositions() 
{
    //получаем список позиций всех заказов

    std::vector<OrderPosition> positionsList;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableOrderPositions());
    while (query.next())
    {
        OrderPosition position; 
        position.setIdPosition(query.value(0).toInt());
        position.setIdOrder(query.value(1).toInt());
        position.setDescription(query.value(2).toString().toStdString());
        position.setQuantity(query.value(3).toString().toStdString());
        position.setIssue(query.value(4).toString().toStdString());
            
        positionsList.push_back(position);
    }

    db.close();

    return positionsList;
}

void DataBase::removeOrder(const int orderId) 
{
    //удаляем Заказ из БД

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("DELETE FROM " + DataBase::getTableOrders() + " WHERE _id=" + QString::number(orderId));

    if (!query.exec()) QMessageBox::warning(0, "", "remove order is unsuccessfully");

    db.close();

    DataBase::removePositionByIdOrder(orderId);

}

void DataBase::editOrder(const Order& editOrder) 
{
    //редактируем заказ

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("UPDATE " + DataBase::getTableOrders() + 
        " SET date=?, client=?, amount=?, payment=?, manager=?, designer=?, availability=?, remark=?, loginCreate=?, loginEdit=?, loginAvailability=?, dateTimeCreate=?, dateTimeEdit=?, dateTimeAvailability=?"
        "  WHERE _id=" + QString::number(editOrder.getId()));
    query.addBindValue(editOrder.getDate().toString("dd.MM.yyyy"));
    query.addBindValue(editOrder.getClient());
    query.addBindValue(QString::fromStdString(editOrder.getAmount()));
    query.addBindValue(QString::fromStdString(editOrder.getPayment()));
    query.addBindValue(editOrder.getManager());
    query.addBindValue(editOrder.getDesigner());
    query.addBindValue(QString::fromStdString(editOrder.getAvailability()));
    query.addBindValue(QString::fromStdString(editOrder.getRemark()));
    query.addBindValue(editOrder.getLoginCreate());
    query.addBindValue(editOrder.getLoginEdit());
    query.addBindValue(editOrder.getLoginAvailability());
    query.addBindValue(editOrder.getDateTimeCreate().toString("dd.MM.yyyy hh:mm"));
    query.addBindValue(editOrder.getDateTimeEdit().toString("dd.MM.yyyy hh:mm"));
    query.addBindValue(editOrder.getDateTimeAvailability().toString("dd.MM.yyyy hh:mm"));

    if (!query.exec()) QMessageBox::warning(0, "", "edit order is unsuccessfully");

    db.close();

    DataBase::removePositionByIdOrder(editOrder.getId());

    for (int i = 0; i < editOrder.getPositionsList().size(); ++i)
    {
        DataBase::addPosition(editOrder.getId(), editOrder.getPositionsList()[i]);
    }
}

void DataBase::setAvailabilityOrder(int orderId, int loginEditId) 
{
    //устанавливаем "готово/в работе" заказа

    Order order(DataBase::getOrder(orderId));
    QDateTime currDateTime = QDateTime::currentDateTime();

    if (order.getAvailability() == "в работе") 
    {
        order.setAvailability("готово");
    }
    else 
    {
        order.setAvailability("в работе");
    }
    order.setLoginAvailability(loginEditId);
    order.setDateTimeAvailability(currDateTime);

    DataBase::editOrder(order);
}

void DataBase::addLogin(const StaffLogin& login) 
{
    //сохраняем логин в БД

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query;
    query.prepare("INSERT INTO " + DataBase::getTableLogins() + " (name, position, login, password)"
        "VALUES (:name, :position, :login, :password);");
    query.bindValue(":name", QString::fromStdString(login.getName()));
    query.bindValue(":position", QString::fromStdString(login.getPosition()));
    query.bindValue(":login", QString::fromStdString(login.getLogin()));
    query.bindValue(":password", QString::fromStdString(login.getPassword()));

    if (!query.exec()) QMessageBox::warning(0, "", "error add Login ");
    db.close();
}

StaffLogin DataBase::getLogin(int loginId) 
{
    //получаем логин из БД

    StaffLogin login;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableLogins() + " WHERE _id=" + QString::number(loginId));

    while (query.next())
    {
        login.setId(loginId);
        login.setName(query.value(1).toString().toStdString());
        login.setPosition(query.value(2).toString().toStdString());
        login.setLogin(query.value(3).toString().toStdString());
        login.setPassword(query.value(4).toString().toStdString());
    }

    db.close();

    return login;
}

std::vector<StaffLogin> DataBase::getLoginsList() 
{
    std::vector<StaffLogin> loginsList;

    QSqlDatabase db;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("OrderBasePrint_dataBase");
        db.setDatabaseName("OrderBasePrint_dataBase.db");
        if (!db.open())
        {
            QMessageBox::warning(0, "", "error open database");
        }
    }

    QSqlQuery query("SELECT * FROM " + DataBase::getTableLogins());
    while (query.next())
    {
        StaffLogin staffLogin; 
        staffLogin.setId(query.value(0).toInt());
        staffLogin.setName(query.value(1).toString().toStdString());
        staffLogin.setPosition(query.value(2).toString().toStdString());
        staffLogin.setLogin(query.value(3).toString().toStdString());
        staffLogin.setPassword(query.value(4).toString().toStdString());
        loginsList.push_back(staffLogin);
    }

    db.close();

    return loginsList;
}