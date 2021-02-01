#include "DataBase.h"
#include <QtWidgets/qmessagebox.h>

const QString DataBase::DB_NAME("OrderBasePrint_dataBase.db");
const QString DataBase::TABLE_ACCOUNTS("accounts");
const QString DataBase::TABLE_CLIENTS("clients");
const QString DataBase::TABLE_STAFFS("staffs");
const QString DataBase::TABLE_ORDERS("orders");
const QString DataBase::TABLE_POSITIONS("positions");
const QString DataBase::TABLE_RECEIPT_COUNT("receiptCounter");

bool DataBase::initDatabase()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_NAME);
    const bool ok = db.open();
    if (!ok) 
    {
        QString error = db.lastError().text();
        QMessageBox::warning(0, "", error);
    }
    return ok;
}

int DataBase::getLastId(const QString& table)
{
    // получаем последний id в таблице БД

    int lastId;

    QSqlQuery query(getDatabase());
    query.exec("SELECT _id FROM " + table + " ORDER BY _id DESC LIMIT 1");

    if (query.first())
        lastId = query.value(0).toInt();

    return query.exec() ? lastId : -1;
}

bool DataBase::incrementReceiptCount()
{
    int count = 0;
    QSqlQuery query(getDatabase());
    query.exec("SELECT * FROM " + TABLE_RECEIPT_COUNT + " WHERE _id=1");

    while (query.next())
        count = query.value(1).toInt();
    
    query.prepare("UPDATE " + TABLE_RECEIPT_COUNT +
        " SET count = ? WHERE _id=1");
    query.addBindValue(++count);

    return query.exec();
}

int DataBase::getReceiptCount()
{
    int count = 0;
    QSqlQuery query(getDatabase());
    query.exec("SELECT * FROM " + TABLE_RECEIPT_COUNT + " WHERE _id=1");

    while (query.next())
        count = query.value(1).toInt();
    return count;
}

std::vector<Client> DataBase::getClientsList()
{
    //получаем список клиентов из БД
    int rowCount = 0;
    QSqlQuery query(getDatabase());
    query.exec("SELECT COUNT(*) FROM " + TABLE_CLIENTS);
    query.first();
    rowCount = query.value(0).toInt();

    std::vector<Client> clientsList;
    clientsList.reserve(rowCount);

    query.exec("SELECT * FROM " + TABLE_CLIENTS);
    
    while (query.next())
    {
        Client client(
            query.value(0).toInt(),
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString(),
            query.value(3).toString().toStdString(),
            query.value(4).toBool());
        clientsList.push_back(std::move(client));
    }

    return clientsList;
}

bool DataBase::addClient(const Client& newClient)
{
    //добавляем клиента в БД

    QSqlQuery query(getDatabase());
    query.prepare("INSERT INTO " + TABLE_CLIENTS + " (name, phone, mail, active)"
        "VALUES (:name, :phone, :mail, :active);");
    query.bindValue(":name", QString::fromStdString(newClient.getName()));
    query.bindValue(":phone", QString::fromStdString(newClient.getPhone()));
    query.bindValue(":mail", QString::fromStdString(newClient.getMail()));
    query.bindValue(":active", newClient.isActive());

    return query.exec();
}

bool DataBase::editClient(const Client& client)
{
    //редактируем клиента

    QSqlQuery query(getDatabase());
    query.prepare("UPDATE " + TABLE_CLIENTS + 
        " SET name = ?, phone = ?, mail = ?, active = ? " +  
        " WHERE _id=" + QString::number(client.getId()));
    query.addBindValue(QString::fromStdString(client.getName()));
    query.addBindValue(QString::fromStdString(client.getPhone()));
    query.addBindValue(QString::fromStdString(client.getMail()));
    query.addBindValue(client.isActive());

    return query.exec();
}

bool DataBase::editClient(const Client* client)
{
    //редактируем клиента

    QSqlQuery query(getDatabase());
    query.prepare("UPDATE " + TABLE_CLIENTS +
        " SET name = ?, phone = ?, mail = ?, active = ? " +
        " WHERE _id=" + QString::number(client->getId()));
    query.addBindValue(QString::fromStdString(client->getName()));
    query.addBindValue(QString::fromStdString(client->getPhone()));
    query.addBindValue(QString::fromStdString(client->getMail()));
    query.addBindValue(client->isActive());

    return query.exec();
}

bool DataBase::removeClient(int id)
{
    //удаляем клиента из БД

    QSqlQuery query(getDatabase());

    return query.exec("DELETE FROM " + TABLE_CLIENTS + " WHERE _id=" + QString::number(id));
}

std::vector<Staff> DataBase::getStaffList()
{
    //получаем список сотрудников из БД
    int rowCount = 0;
    QSqlQuery query(getDatabase());
    query.exec("SELECT COUNT(*) FROM " + TABLE_STAFFS);
    query.first();
    rowCount = query.value(0).toInt();

    std::vector<Staff> staffList;
    staffList.reserve(rowCount);

    query.exec("SELECT * FROM " + TABLE_STAFFS);
    while (query.next())
    {
        Staff staff(
            query.value(0).toInt(),
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString(),
            query.value(3).toBool());
        staffList.push_back(std::move(staff));
    }

    return staffList;
}

bool DataBase::addStaff(const Staff& newStaff)
{
    //добавляем сотрудника в БД

    QSqlQuery query(getDatabase());
    query.prepare("INSERT INTO " + TABLE_STAFFS + " (name, position, active)"
        "VALUES (:name, :position, :active);");
    query.bindValue(":name", QString::fromStdString(newStaff.getName()));
    query.bindValue(":position", QString::fromStdString(newStaff.getPosition()));
    query.bindValue(":active", newStaff.isActive());

    return query.exec();
}

bool DataBase::editStaff(const Staff& editStaff)
{
    //редактируем сотрудника

    QSqlQuery query(getDatabase());
    query.prepare("UPDATE " + TABLE_STAFFS + " SET name = ?, position = ?, active = ?  WHERE _id=" + QString::number(editStaff.getId()));
    query.addBindValue(QString::fromStdString(editStaff.getName()));
    query.addBindValue(QString::fromStdString(editStaff.getPosition()));
    query.addBindValue(editStaff.isActive());

    return query.exec();
}

bool DataBase::editStaff(const Staff* editStaff)
{
    //редактируем сотрудника

    QSqlQuery query(getDatabase());
    query.prepare("UPDATE " + TABLE_STAFFS + " SET name = ?, position = ?, active = ?  WHERE _id=" + QString::number(editStaff->getId()));
    query.addBindValue(QString::fromStdString(editStaff->getName()));
    query.addBindValue(QString::fromStdString(editStaff->getPosition()));
    query.addBindValue(editStaff->isActive());

    return query.exec();
}

bool DataBase::removeStaff(int staffId)
{
    //удаляем сотрудника из БД

    QSqlQuery query(getDatabase());

    return query.exec("DELETE FROM " + TABLE_STAFFS + " WHERE _id=" + QString::number(staffId));
}

std::vector<Order> DataBase::getOrdersList()
{
    //получаем список заказов
    int rowCount = 0;
    QSqlQuery query(getDatabase());
    query.exec("SELECT COUNT(*) FROM " + TABLE_ORDERS);
    query.first();
    rowCount = query.value(0).toInt();

    std::vector<Order> ordersList;
    ordersList.reserve(rowCount);

    query.exec("SELECT * FROM " + TABLE_ORDERS);
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

bool DataBase::addOrder(const Order& order)
{
    //добавляем заказ в БД
    bool successful = false;
    QSqlQuery query(getDatabase());
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
        successful = true;
    else
        return false;

    if (successful)
    {
        int orderId = DataBase::getLastId(TABLE_ORDERS);
        for (size_t i = 0; i < order.getPositionsList().size(); ++i)
            DataBase::addPosition(DataBase::getLastId(TABLE_ORDERS), order.getPositionsList()[i]);
        return true;        
    }
    else
        return false;
}

bool DataBase::editOrder(const Order* editOrder)
{
    //редактируем заказ
    bool successful = false;
    QSqlQuery query(getDatabase());
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
        successful = true;
    else
        return false;

    if (successful)
    {
        DataBase::removePositionByIdOrder(editOrder->getId());

        size_t i = 0;
        for (; i < editOrder->getPositionsList().size(); ++i)
            DataBase::addPosition(editOrder->getId(), editOrder->getPositionsList()[i]);
        return true;
    }
    else
        return false;
}

bool DataBase::editOrder(const Order& editOrder)
{
    //редактируем заказ
    bool successful = false;
    QSqlQuery query(getDatabase());
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
        successful = true;
    else
        return false;

    if (!successful) return false;

    DataBase::removePositionByIdOrder(editOrder.getId());

    for (size_t i = 0; i < editOrder.getPositionsList().size(); ++i)
        DataBase::addPosition(editOrder.getId(), editOrder.getPositionsList()[i]);

    return true;
}

bool DataBase::removeOrder(int orderId)
{
    //удаляем Заказ из БД

    QSqlQuery query(getDatabase());

    if (!query.exec("DELETE FROM " + TABLE_ORDERS + " WHERE _id=" + QString::number(orderId)))
        return false;
    else
    {
        DataBase::removePositionByIdOrder(orderId);
        return true;
    }
}

std::vector<OrderPosition> DataBase::getOrderPositionsList(int orderId)
{
    //получаем список позиций по id заказа
    int rowCount = 0;
    QSqlQuery query(getDatabase());
    query.exec("SELECT COUNT(*) FROM " + TABLE_POSITIONS);
    query.first();
    rowCount = query.value(0).toInt();

    std::vector<OrderPosition> positionsList;
    positionsList.reserve(rowCount);

    query.exec("SELECT * FROM " + TABLE_POSITIONS + " WHERE idOrder=" + QString::number(orderId));
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
    int rowCount = 0;

    QSqlQuery query(getDatabase());
    query.exec("SELECT COUNT(*) FROM " + TABLE_POSITIONS);
    query.first();
    rowCount = query.value(0).toInt();

    std::vector<OrderPosition> positionsList;
    positionsList.reserve(rowCount);

    query.exec("SELECT * FROM " + TABLE_POSITIONS);
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

bool DataBase::addPosition(int orderId, const OrderPosition& position)
{
    QSqlQuery query(getDatabase());
    query.prepare("INSERT INTO " + TABLE_POSITIONS + " (idOrder, description, quantity, issue)"
        " VALUES (:idOrder, :description, :quantity, :issue);");

    query.bindValue(":idOrder", orderId);
    query.bindValue(":description", QString::fromStdString(position.getDescription()));
    query.bindValue(":quantity", QString::fromStdString(position.getQuantity()));
    query.bindValue(":issue", QString::fromStdString(position.getIssue()));
    return query.exec();
}

bool DataBase::editPosition(const OrderPosition& editPosition)
{
    QSqlQuery query(getDatabase());
    query.prepare("UPDATE " + TABLE_POSITIONS +
        " SET description=?, quantity=?, issue=?"
        "  WHERE _id=" + QString::number(editPosition.getIdPosition()));
    query.addBindValue(QString::fromStdString(editPosition.getDescription()));
    query.addBindValue(QString::fromStdString(editPosition.getQuantity()));
    query.addBindValue(QString::fromStdString(editPosition.getIssue()));

    return query.exec();
}

bool DataBase::removePositionById(int idPosition)
{
    QSqlQuery query(getDatabase());
    return query.exec("DELETE FROM " + TABLE_POSITIONS + " WHERE _id=" + QString::number(idPosition));
}

bool DataBase::removePositionByIdOrder(int idOrder)
{
    QSqlQuery query("DELETE FROM " + TABLE_POSITIONS + " WHERE idOrder=" + QString::number(idOrder));
    return query.exec();
}

std::vector<StaffAccount> DataBase::getAccountsList()
{
    int rowCount = 0;
    QSqlQuery query(getDatabase());
    query.exec("SELECT COUNT(*) FROM " + TABLE_ACCOUNTS);
    query.first();
    rowCount = query.value(0).toInt();

    std::vector<StaffAccount> accountsList;
    accountsList.reserve(rowCount);

    query.exec("SELECT * FROM " + TABLE_ACCOUNTS);
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

bool DataBase::addAccount(const StaffAccount& newAccount)
{
    //сохраняем логин в БД

    QSqlQuery query(getDatabase());
    query.prepare("INSERT INTO " + TABLE_ACCOUNTS + " (name, position, login, password)"
        "VALUES (:name, :position, :login, :password);");
    query.bindValue(":name", QString::fromStdString(newAccount.getName()));
    query.bindValue(":position", QString::fromStdString(newAccount.getPosition()));
    query.bindValue(":login", QString::fromStdString(newAccount.getLogin()));
    query.bindValue(":password", QString::fromStdString(newAccount.getPassword()));

    return query.exec();
}