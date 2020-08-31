#include "DataBase.h"
#include <vector>
#include <qfile.h>
#include <qtextstream.h>
#include <qstring.h>

void DataBase::connectToDataBase() 
{
    // подключаемся к базе данных
}

std::vector<Client> DataBase::getClientsList() 
{
    //получаем список клиентов из БД

    QFile file(DataBase::getTableClients());
    std::vector<Client> clientsList;
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            Client client;

            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));
            client.setId(tokens[0]);
            client.setName(tokens[1]);
            client.setPhone(tokens[2]);
            client.setMail(tokens[3]);
            clientsList.push_back(client);
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    return clientsList;
}

void DataBase::addClient(const Client& newClient) 
{
    //добавляем клиента в БД

    QFile file(DataBase::getTableClients());
    if (file.open(QIODevice::Append)) 
    {
        QTextStream stream(&file);

        stream << QString::fromStdString(std::to_string(newClient.getId()) + "~" + newClient.getName() + "~" + newClient.getPhone() + "~" + newClient.getMail() + "\r\n");
        file.close();

        if (stream.status() != QTextStream::Ok) 
        {
            //qDebug() << "Ошибка записи файла";
        }
    }
}

Client DataBase::getClient(int clientId) 
{
    //получаем клиента по id

    Client client;
    QFile file(DataBase::getTableClients());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));
            if (std::stoi(tokens[0]) == clientId) 
            {
                client.setId(tokens[0]);
                client.setName(tokens[1]);
                client.setPhone(tokens[2]);
                client.setMail(tokens[3]);
            }
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    return client;
}

void DataBase::removeClient(int id) 
{
    //удаляем клиента из БД

    QFile newFile("temp.txt");
    QFile file(DataBase::getTableClients());


    if (newFile.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFile);

        for (int i = 0; i < DataBase::getClientsList().size(); ++i)
        {
            if (DataBase::getClientsList()[i].getId() != id) 
            {
                stream << QString::fromStdString(std::to_string(
                      DataBase::getClientsList()[i].getId()) + "~"
                    + DataBase::getClientsList()[i].getName() + "~"
                    + DataBase::getClientsList()[i].getPhone() + "~"
                    + DataBase::getClientsList()[i].getMail() + "\r\n");
            }
        }
        newFile.close();
    }
    file.remove();
    newFile.rename(DataBase::getTableClients());
}

int DataBase::getLastId(const QString& table) 
{
    // получаем последний id в таблице БД

    int lastId;
    QFile file(table);
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));
            lastId = std::stoi(tokens[0]);
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
            lastId = 0;
        }
        file.close();
    }
    else lastId = 0;

    return lastId;
}

void DataBase::editClient(const Client& client) 
{
    //редактируем клиента

    QFile newFile("temp.txt");
    QFile file(DataBase::getTableClients());

    if (newFile.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFile);

        for (int i = 0; i < DataBase::getClientsList().size(); ++i)
        {
            if (DataBase::getClientsList()[i].getId() != client.getId()) 
            {
                stream << QString::fromStdString(std::to_string(
                    DataBase::getClientsList()[i].getId()) + "~"
                    + DataBase::getClientsList()[i].getName() + "~"
                    + DataBase::getClientsList()[i].getPhone() + "~"
                    + DataBase::getClientsList()[i].getMail() + "\r\n");
            }
            else 
            {
                stream << QString::fromStdString(std::to_string(
                    client.getId()) + "~"
                    + client.getName() + "~"
                    + client.getPhone() + "~"
                    + client.getMail() + "\r\n");
            }
        }
        newFile.close();
    }

    file.remove();
    newFile.rename(DataBase::getTableClients());
}

std::vector<Staff> DataBase::getStaffList() 
{
    //получаем список сотрудников из БД

    std::vector<Staff> staffList;
    QFile file(DataBase::getTableStaff());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            Staff staff;

            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));
            staff.setId(tokens[0]);
            staff.setPosition(tokens[1]);
            staff.setName(tokens[2]);
            staffList.push_back(staff);
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }
    return staffList;
}

void DataBase::addStaff(const Staff& newStaff) 
{
    //добавляем сотрудника в БД

    QFile file(DataBase::getTableStaff());
    if (file.open(QIODevice::Append)) 
    {
        QTextStream stream(&file);

        stream << QString::fromStdString(
            std::to_string(newStaff.getId()) + "~" + 
            newStaff.getPosition() + "~" + 
            newStaff.getName() + 
            "\r\n");
        file.close();

        if (stream.status() != QTextStream::Ok) 
        {
            //qDebug() << "Ошибка записи файла";
        }
    }
}

Staff DataBase::getStaff(int staffId) 
{
    //получаем сотрудника по id
    Staff staff;
    QFile file(DataBase::getTableStaff());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));

            if (std::stoi(tokens[0]) == staffId) 
            {
                staff.setId(tokens[0]);
                staff.setPosition(tokens[1]);
                staff.setName(tokens[2]);
            }

        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    return staff;
}

void DataBase::removeStaff(int staffId) 
{
    //удаляем сотрудника из БД

    QFile newFile("temp.txt");
    QFile file(DataBase::getTableStaff());

    if (newFile.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFile);

        for (int i = 0; i < DataBase::getStaffList().size(); ++i)
        {
            if (DataBase::getStaffList()[i].getId() != staffId) 
            {
                stream << QString::fromStdString(
                    std::to_string(DataBase::getStaffList()[i].getId()) + "~" + 
                    DataBase::getStaffList()[i].getPosition() + "~" + 
                    DataBase::getStaffList()[i].getName() + 
                    "\r\n");
            }
        }
        newFile.close();
    }
    file.remove();
    newFile.rename(DataBase::getTableStaff());
}

void DataBase::editStaff(const Staff& editStaff) 
{
    //редактируем сотрудника

    QFile newFile("temp.txt");
    QFile file(DataBase::getTableStaff());
    if (newFile.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFile);

        for (int i = 0; i < DataBase::getStaffList().size(); ++i)
        {
            if (DataBase::getStaffList()[i].getId() != editStaff.getId()) 
            {
                stream << QString::fromStdString(std::to_string(
                    DataBase::getStaffList()[i].getId()) + "~" + 
                    DataBase::getStaffList()[i].getPosition() + "~" + 
                    DataBase::getStaffList()[i].getName() + 
                    "\r\n");
            }
            else 
            {
                stream << QString::fromStdString(std::to_string(
                    editStaff.getId()) + "~" + 
                    editStaff.getPosition() + "~" + 
                    editStaff.getName() + 
                    "\r\n");
            }
        }
        newFile.close();
    }

    file.remove();
    newFile.rename(DataBase::getTableStaff());
}

void DataBase::addOrder(const Order& order) 
{
    //добавляем заказ в БД
    QFile file(DataBase::getTableOrders());
    if (file.open(QIODevice::Append)) 
    {
        QTextStream stream(&file);

        stream << QString::fromStdString(
            std::to_string(order.getId()) + "~" +
            order.getDate().toString("dd.MM.yyyy").toStdString() + "~" +
            std::to_string(order.getClient().getId()) + "~" +
            order.getAmount() + "~" +
            order.getPayment() + "~" +
            std::to_string(order.getManager().getId()) + "~" +
            std::to_string(order.getDesigner().getId()) + "~" +
            order.getAvailability() + "~" +
            order.getRemark() + "~" +
            std::to_string(order.getLoginCreate()) + "~" +
            std::to_string(order.getLoginEdit()) + "~" +
            std::to_string(order.getLoginAvailability()) + "~" +
            order.getDateTimeCreate().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
            order.getDateTimeEdit().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
            order.getDateTimeAvailability().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
            "\r\n");
        file.close();

        if (stream.status() != QTextStream::Ok) 
        {
            //qDebug() << "Ошибка записи файла";
        }
    }

    QFile filePositions(DataBase::getTableOrderPositions());
    if (filePositions.open(QIODevice::Append)) 
    {
        QTextStream stream(&filePositions);

        for (int i = 0; i < order.getPositionsList().size(); ++i)
        {
            stream << QString::fromStdString(
                std::to_string(order.getPositionsList()[i].getIdPosition()) + "~" +
                std::to_string(order.getPositionsList()[i].getIdOrder()) + "~" +
                order.getPositionsList()[i].getDescription() + "~" +
                order.getPositionsList()[i].getIssue() + "~" +
                order.getPositionsList()[i].getQuantity() + "~" +
                "\r\n");
        }

        filePositions.close();

        if (stream.status() != QTextStream::Ok) {
            //qDebug() << "Ошибка записи файла";
        }
    }
}

Order DataBase::getOrder(int orderId) 
{
    //получаем заказ из БД по id

    Order order;

    QFile file(DataBase::getTableOrders());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));

            if (std::stoi(tokens[0]) == orderId) 
            {
                order.setId(std::stoi(tokens[0]));
                QDate date = QDate::fromString(QString::fromStdString(tokens[1]), "dd.MM.yyyy");
                order.setDate(date);
                if (std::stoi(tokens[2]) != 0) 
                {
                    order.setClient(DataBase::getClient(std::stoi(tokens[2])));
                }
                else order.setClient(Client(0, "", "", ""));
                order.setAmount(tokens[3]);
                order.setPayment(tokens[4]);
                if (std::stoi(tokens[5]) != 0) 
                {
                    order.setManager(DataBase::getStaff(std::stoi(tokens[5])));
                }
                else order.setManager(Staff(0));
                if (std::stoi(tokens[6]) != 0) {
                    order.setDesigner(DataBase::getStaff(std::stoi(tokens[6])));
                }
                else order.setDesigner(Staff(0));
                order.setAvailability(tokens[7]);
                order.setRemark(tokens[8]);
                order.setLoginCreate(std::stoi(tokens[9]));
                order.setLoginEdit(std::stoi(tokens[10]));
                order.setLoginAvailability(std::stoi(tokens[11]));
                QDateTime dateTime = QDateTime::fromString(QString::fromStdString(tokens[12]), "dd.MM.yyyy hh:mm");
                order.setDateTimeCreate(dateTime);
                dateTime = QDateTime::fromString(QString::fromStdString(tokens[13]), "dd.MM.yyyy hh:mm");
                order.setDateTimeEdit(dateTime);
                dateTime = QDateTime::fromString(QString::fromStdString(tokens[14]), "dd.MM.yyyy hh:mm");
                order.setDateTimeAvailability(dateTime);
            }
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    order.setPositionsList(DataBase::getOrderPositionsList(order.getId()));

    return order;
}

std::vector<Order> DataBase::getOrdersList() 
{
    //получаем список заказов

    std::vector<Order> ordersList;
    QFile file(DataBase::getTableOrders());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            Order order;

            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));
            order.setId(std::stoi(tokens[0]));
            QDate date = QDate::fromString(QString::fromStdString(tokens[1]), "dd.MM.yyyy");
            order.setDate(date);
            order.setClient(DataBase::getClient(std::stoi(tokens[2])));
            order.setAmount(tokens[3]);
            order.setPayment(tokens[4]);
            order.setManager(DataBase::getStaff(std::stoi(tokens[5])));
            order.setDesigner(DataBase::getStaff(std::stoi(tokens[6])));
            order.setAvailability(tokens[7]);
            order.setRemark(tokens[8]);
            order.setLoginCreate(std::stoi(tokens[9]));
            order.setLoginEdit(std::stoi(tokens[10]));
            order.setLoginAvailability(std::stoi(tokens[11]));
            QDateTime dateTime = QDateTime::fromString(QString::fromStdString(tokens[12]), "dd.MM.yyyy hh:mm");
            order.setDateTimeCreate(dateTime);
            dateTime = QDateTime::fromString(QString::fromStdString(tokens[13]), "dd.MM.yyyy hh:mm");
            order.setDateTimeEdit(dateTime);
            dateTime = QDateTime::fromString(QString::fromStdString(tokens[14]), "dd.MM.yyyy hh:mm");
            order.setDateTimeAvailability(dateTime);

            ordersList.push_back(order);
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    return ordersList;
}

std::vector<OrderPosition> DataBase::getOrderPositionsList(int orderId) 
{
    //получаем список позиций по id заказа

    std::vector<OrderPosition> positionsList;
    QFile file(DataBase::getTableOrderPositions());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            OrderPosition position;

            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));

            if (orderId == std::stoi(tokens[1])) 
            {
                position.setIdOrder(std::stoi(tokens[1]));
                position.setIdPosition(std::stoi(tokens[0]));
                position.setDescription(tokens[2]);
                position.setIssue(tokens[3]);
                position.setQuantity(tokens[4]);

                positionsList.push_back(position);
            }
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    return positionsList;
}

std::vector<OrderPosition> DataBase::getAllPositions() 
{
    //получаем список позиций всех заказов

    std::vector<OrderPosition> positionsList;
    QFile file(DataBase::getTableOrderPositions());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            OrderPosition position;

            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));

            position.setIdPosition(std::stoi(tokens[0]));
            position.setIdOrder(std::stoi(tokens[1]));
            position.setDescription(tokens[2]);
            position.setIssue(tokens[3]);
            position.setQuantity(tokens[4]);

            positionsList.push_back(position);
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    return positionsList;
}

void DataBase::removeOrder(int orderId) 
{
    //удаляем Заказ из БД

    QFile newFile("temp.txt");
    QFile file(DataBase::getTableOrders());

    if (newFile.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFile);
        std::vector<Order>* ordersList = new std::vector<Order>(DataBase::getOrdersList());

        for (int i = 0; i < ordersList->size(); ++i)
        {
            if ((*ordersList)[i].getId() != orderId) 
            {
                stream << QString::fromStdString(
                    std::to_string((*ordersList)[i].getId()) + "~" +
                    (*ordersList)[i].getDate().toString("dd.MM.yyyy").toStdString() + "~" +
                    std::to_string((*ordersList)[i].getClient().getId()) + "~" +
                    (*ordersList)[i].getAmount() + "~" +
                    (*ordersList)[i].getPayment() + "~" +
                    std::to_string((*ordersList)[i].getManager().getId()) + "~" +
                    std::to_string((*ordersList)[i].getDesigner().getId()) + "~" +
                    (*ordersList)[i].getAvailability() + "~" +
                    (*ordersList)[i].getRemark() + "~" +
                    std::to_string((*ordersList)[i].getLoginCreate()) + "~" +
                    std::to_string((*ordersList)[i].getLoginEdit()) + "~" +
                    std::to_string((*ordersList)[i].getLoginAvailability()) + "~" +
                    (*ordersList)[i].getDateTimeCreate().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    (*ordersList)[i].getDateTimeEdit().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    (*ordersList)[i].getDateTimeAvailability().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    "\r\n");
                file.close();

                if (stream.status() != QTextStream::Ok) 
                {
                    //qDebug() << "Ошибка записи файла";
                }
            }
        }
        newFile.close();
        delete ordersList;
    }
    file.remove();
    newFile.rename(DataBase::getTableOrders());

    QFile newFilePositions("temp2.txt");
    QFile filePositions(DataBase::getTableOrderPositions());

    if (newFilePositions.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFilePositions);
        std::vector<OrderPosition>* orderPositionsList = new std::vector<OrderPosition>(DataBase::getAllPositions());

        for (int i = 0; i < orderPositionsList->size(); ++i)
        {
            if ((*orderPositionsList)[i].getIdOrder() != orderId) 
            {
                stream << QString::fromStdString(
                    std::to_string((*orderPositionsList)[i].getIdPosition()) + "~" +
                    std::to_string((*orderPositionsList)[i].getIdOrder()) + "~" +
                    (*orderPositionsList)[i].getDescription() + "~" +
                    (*orderPositionsList)[i].getIssue() + "~" +
                    (*orderPositionsList)[i].getQuantity() + "~" +
                    "\r\n");
            }
        }
        newFilePositions.close();
        delete orderPositionsList;
    }
    filePositions.remove();
    newFilePositions.rename(DataBase::getTableOrderPositions());
}

void DataBase::editOrder(const Order& editOrder) 
{
    //редактируем заказ

    QFile newFile("temp.txt");
    QFile file(DataBase::getTableOrders());

    std::vector<Order>* ordersList = new std::vector<Order>(DataBase::getOrdersList());

    if (newFile.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFile);

        for (int i = 0; i < ordersList->size(); ++i)
        {
            if ((*ordersList)[i].getId() != editOrder.getId()) 
            {
                stream << QString::fromStdString(
                    std::to_string((*ordersList)[i].getId()) + "~" +
                    (*ordersList)[i].getDate().toString("dd.MM.yyyy").toStdString() + "~" +
                    std::to_string((*ordersList)[i].getClient().getId()) + "~" +
                    (*ordersList)[i].getAmount() + "~" +
                    (*ordersList)[i].getPayment() + "~" +
                    std::to_string((*ordersList)[i].getManager().getId()) + "~" +
                    std::to_string((*ordersList)[i].getDesigner().getId()) + "~" +
                    (*ordersList)[i].getAvailability() + "~" +
                    (*ordersList)[i].getRemark() + "~" +
                    std::to_string((*ordersList)[i].getLoginCreate()) + "~" +
                    std::to_string((*ordersList)[i].getLoginEdit()) + "~" +
                    std::to_string((*ordersList)[i].getLoginAvailability()) + "~" +
                    (*ordersList)[i].getDateTimeCreate().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    (*ordersList)[i].getDateTimeEdit().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    (*ordersList)[i].getDateTimeAvailability().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    "\r\n");
            }
            else 
            {
                stream << QString::fromStdString(
                    std::to_string(editOrder.getId()) + "~" +
                    editOrder.getDate().toString("dd.MM.yyyy").toStdString() + "~" +
                    std::to_string(editOrder.getClient().getId()) + "~" +
                    editOrder.getAmount() + "~" +
                    editOrder.getPayment() + "~" +
                    std::to_string(editOrder.getManager().getId()) + "~" +
                    std::to_string(editOrder.getDesigner().getId()) + "~" +
                    editOrder.getAvailability() + "~" +
                    editOrder.getRemark() + "~" +
                    std::to_string(editOrder.getLoginCreate()) + "~" +
                    std::to_string(editOrder.getLoginEdit()) + "~" +
                    std::to_string(editOrder.getLoginAvailability()) + "~" +
                    editOrder.getDateTimeCreate().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    editOrder.getDateTimeEdit().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    editOrder.getDateTimeAvailability().toString("dd.MM.yyyy hh:mm").toStdString() + "~" +
                    "\r\n");
            }
        }
        newFile.close();
    }
    delete ordersList;

    file.remove();
    newFile.rename(DataBase::getTableOrders());

    std::vector<OrderPosition>* positionsList = new std::vector<OrderPosition>(DataBase::getAllPositions());
    QFile newFilePositions("temp2.txt");
    QFile filePositions(DataBase::getTableOrderPositions());
    if (newFilePositions.open(QIODevice::WriteOnly)) 
    {
        QTextStream stream(&newFilePositions);

        for (int i = 0; i < positionsList->size(); ++i)
        {
            if (editOrder.getId() != (*positionsList)[i].getIdOrder()) 
            {
                stream << QString::fromStdString(
                    std::to_string((*positionsList)[i].getIdPosition()) + "~" +
                    std::to_string((*positionsList)[i].getIdOrder()) + "~" +
                    (*positionsList)[i].getDescription() + "~" +
                    (*positionsList)[i].getIssue() + "~" +
                    (*positionsList)[i].getQuantity() + "~" +
                    "\r\n");
            }
        }
        newFilePositions.close();

        if (stream.status() != QTextStream::Ok) 
        {
            //qDebug() << "Ошибка записи файла";
        }
    }
    delete positionsList;

    if (newFilePositions.open(QIODevice::Append)) 
    {
        QTextStream stream(&newFilePositions);
        for (int i = 0; i < editOrder.getPositionsList().size(); ++i)
        {
            stream << QString::fromStdString(
                std::to_string(editOrder.getPositionsList()[i].getIdPosition()) + "~" +
                std::to_string(editOrder.getId()) + "~" +
                editOrder.getPositionsList()[i].getDescription() + "~" +
                editOrder.getPositionsList()[i].getIssue() + "~" +
                editOrder.getPositionsList()[i].getQuantity() + "~" +
                "\r\n");
        }
    }

    filePositions.remove();
    newFilePositions.rename(DataBase::getTableOrderPositions());
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

    QFile file(DataBase::getTableLogins());
    if (file.open(QIODevice::Append)) 
    {
        QTextStream stream(&file);

        stream << QString::fromStdString(std::to_string(
            login.getId()) + "~" + 
            login.getName() + "~" + 
            login.getPosition() + "~" + 
            login.getLogin() + "~" + 
            login.getPassword() + 
            "\r\n");
        file.close();

        if (stream.status() != QTextStream::Ok) 
        {
            //qDebug() << "Ошибка записи файла";
        }
    }
}

StaffLogin DataBase::getLogin(int loginId) 
{
    //получаем логин из БД
    StaffLogin login;
    QFile file(DataBase::getTableLogins());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));

            if (std::stoi(tokens[0]) == loginId) 
            {
                login.setId(tokens[0]);
                login.setName(tokens[1]);
                login.setPosition(tokens[2]);
                login.setLogin(tokens[3]);
                login.setPassword(tokens[4]);
            }
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }
    return login;
}

std::vector<StaffLogin> DataBase::getLoginsList() 
{
    std::vector<StaffLogin> loginsList;
    QFile file(DataBase::getTableLogins());
    char sep = '~';

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            StaffLogin login;

            std::vector<std::string> tokens;
            std::string s = stream.readLine().toStdString();
            for (size_t p = 0, q = 0; p != s.npos; p = q)
                tokens.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));
            login.setId(tokens[0]);
            login.setName(tokens[1]);
            login.setPosition(tokens[2]);
            login.setLogin(tokens[3]);
            login.setPassword(tokens[4]);
            loginsList.push_back(login);
        }

        if (stream.status() != QTextStream::Ok)
        {
            //qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }

    return loginsList;
}


/*
bool DataBase::restoreDataBase()
{

}

bool DataBase::openDataBase()
{

}


void DataBase::closeDataBase()
{

}
*/
