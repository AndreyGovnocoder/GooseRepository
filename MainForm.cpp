#include "MainForm.h"
#include "qmessagebox.h"
#include <qdebug.h>

std::vector<Order> MainForm::_ordersList;
std::vector<Client> MainForm::_clientsList;
std::vector<Staff> MainForm::_staffsList;
std::vector<OrderPosition> MainForm::_positionsList;
std::vector<StaffAccount> MainForm::_accountsList;

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
{    
    ui.setupUi(this);    
    connect(ui.ordersTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    ui.ordersTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    _ordersList = DataBase::getOrdersList();
    _clientsList = DataBase::getClientsList();
    _staffsList = DataBase::getStaffList();
    _positionsList = DataBase::getAllPositions();
    _accountsList = DataBase::getAccountsList();
    setOrdersTableWidget();
    setTransparentClientCard();  
}

void MainForm::setTransparentClientCard() 
{
    //делаем поля карты клиенты прозрачными 

    QPalette palette = ui.clientNameLineEdit->palette();

    palette.setColor(QPalette::Active, QPalette::Base, Qt::transparent);
    palette.setColor(QPalette::Inactive, QPalette::Base, Qt::transparent);

    ui.clientNameLineEdit->setPalette(palette);
    ui.clientPhoneLineEdit->setPalette(palette);
    ui.clientMailLineEdit->setPalette(palette);
}

void MainForm::clearClientCard() 
{
    //очищаем карту клиента

    ui.clientNameLineEdit->clear();
    ui.clientPhoneLineEdit->clear();
    ui.clientMailLineEdit->clear();
}

void MainForm::clearRemark() 
{
    //очищаем примечание

    ui.remarkTextEdit->clear();
}

void MainForm::setOrdersTableWidget() 
{
    ui.ordersTableWidget->clearContents();
    ui.ordersTableWidget->setRowCount(0);

    int orderId;
    QString date;
    Client* client;
    QString payment;
    QString amount;
    Staff* manager;
    QString availability;

    size_t i = 0;
    for (; i < _ordersList.size(); ++i)
    {
        
        orderId = _ordersList[i].getId();
        date = _ordersList[i].getDate().toString("dd.MM.yyyy");
        client = findClient(_ordersList[i].getClient());
        payment = QString::fromStdString(_ordersList[i].getPayment());
        amount = QString::fromStdString(_ordersList[i].getAmount());
        availability = QString::fromStdString(_ordersList[i].getAvailability());

        QTableWidgetItem* orderIdItem = new QTableWidgetItem(QString::number(orderId));
        orderIdItem->setData(Qt::UserRole, orderId);
        QTableWidgetItem* dateItem = new QTableWidgetItem(date);
        QTableWidgetItem* clientItem = new QTableWidgetItem(QString::fromStdString(client->getName()));
        clientItem->setData(Qt::UserRole, client->getId());
        QTableWidgetItem* paymentItem = new QTableWidgetItem(payment);
        QTableWidgetItem* amountItem = new QTableWidgetItem(amount);
        QTableWidgetItem* managerItem = new QTableWidgetItem();
        QTableWidgetItem* designerItem = new QTableWidgetItem();

        if (Staff* designer = findStaff(_ordersList[i].getDesigner()))
        {
            designerItem->setText(QString::fromStdString(designer->getName()));
            designerItem->setData(Qt::UserRole, designer->getId());
        }
            
        if (findStaff(_ordersList[i].getManager()) != nullptr)
        {
            manager = findStaff(_ordersList[i].getManager());
            if (manager->getId() > 0)
            {
                managerItem->setText(QString::fromStdString(manager->getName()));
                managerItem->setData(Qt::UserRole, manager->getId());
            }
        }
        
        QTableWidgetItem* availabilityItem = new QTableWidgetItem(availability);

        ui.ordersTableWidget->insertRow(i);
        ui.ordersTableWidget->setItem(i, 0, orderIdItem);
        ui.ordersTableWidget->setItem(i, 1, dateItem);
        ui.ordersTableWidget->setItem(i, 2, clientItem);
        ui.ordersTableWidget->setItem(i, 3, paymentItem);
        ui.ordersTableWidget->setItem(i, 4, amountItem);
        ui.ordersTableWidget->setItem(i, 5, managerItem);
        ui.ordersTableWidget->setItem(i, 6, designerItem);
        ui.ordersTableWidget->setItem(i, 7, availabilityItem);
    }

    ui.ordersTableWidget->hideColumn(0);
    ui.ordersTableWidget->resizeColumnsToContents();
    ui.ordersTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui.ordersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainForm::setOrdersTableWidget(const std::vector<Order*>& ordersList)
{
    ui.ordersTableWidget->clearContents();
    ui.ordersTableWidget->setRowCount(0);

    int orderId;
    QString date;
    Client* client;
    QString payment;
    QString amount;
    Staff* manager;
    Staff* designer;
    QString availability;

    size_t i = 0;
    for (; i < ordersList.size(); ++i)
    {

        orderId = ordersList[i]->getId();
        date = ordersList[i]->getDate().toString("dd.MM.yyyy");
        client = findClient(ordersList[i]->getClient());
        payment = QString::fromStdString(ordersList[i]->getPayment());
        amount = QString::fromStdString(ordersList[i]->getAmount());
        availability = QString::fromStdString(ordersList[i]->getAvailability());

        QTableWidgetItem* orderIdItem = new QTableWidgetItem(QString::number(orderId));
        orderIdItem->setData(Qt::UserRole, orderId);
        QTableWidgetItem* dateItem = new QTableWidgetItem(date);
        QTableWidgetItem* clientItem = new QTableWidgetItem(QString::fromStdString(client->getName()));
        clientItem->setData(Qt::UserRole, client->getId());
        QTableWidgetItem* paymentItem = new QTableWidgetItem(payment);
        QTableWidgetItem* amountItem = new QTableWidgetItem(amount);
        QTableWidgetItem* managerItem = new QTableWidgetItem();
        QTableWidgetItem* designerItem = new QTableWidgetItem();

        if (findStaff(ordersList[i]->getDesigner()) != nullptr)
        {
            designer = findStaff(ordersList[i]->getDesigner());
            if (designer->getId() > 0)
            {
                designerItem->setText(QString::fromStdString(designer->getName()));
                designerItem->setData(Qt::UserRole, designer->getId());
            }
        }

        if (findStaff(ordersList[i]->getManager()) != nullptr)
        {
            manager = findStaff(ordersList[i]->getManager());
            if (manager->getId() > 0)
            {
                managerItem->setText(QString::fromStdString(manager->getName()));
                managerItem->setData(Qt::UserRole, manager->getId());
            }
        }

        QTableWidgetItem* availabilityItem = new QTableWidgetItem(availability);

        ui.ordersTableWidget->insertRow(i);
        ui.ordersTableWidget->setItem(i, 0, orderIdItem);
        ui.ordersTableWidget->setItem(i, 1, dateItem);
        ui.ordersTableWidget->setItem(i, 2, clientItem);
        ui.ordersTableWidget->setItem(i, 3, paymentItem);
        ui.ordersTableWidget->setItem(i, 4, amountItem);
        ui.ordersTableWidget->setItem(i, 5, managerItem);
        ui.ordersTableWidget->setItem(i, 6, designerItem);
        ui.ordersTableWidget->setItem(i, 7, availabilityItem);
    }

    ui.ordersTableWidget->hideColumn(0);
    ui.ordersTableWidget->resizeColumnsToContents();
    ui.ordersTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui.ordersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainForm::clearPositionsTableWidget()
{
    ui.positionsTableWidget->clearContents();
    ui.positionsTableWidget->setRowCount(0);
}

void MainForm::setPositionsTableWidget(const Order* order) 
{
    //заполняем таблицу позиций выделенного заказа

    std::vector<OrderPosition> positionsList = order->getPositionsList();
    int positionId;
    QString description;
    QStringList descriptionList;
    QString quantity;
    QString issue;

    ui.positionsTableWidget->clearContents();
    ui.positionsTableWidget->setRowCount(0);
    ui.positionsTableWidget->hideColumn(0);

    size_t i = 0;
    for (; i < positionsList.size(); ++i)
    {
        QString descr;
        positionId = positionsList[i].getIdPosition();
        description = QString::fromStdString(positionsList[i].getDescription());
        descriptionList = description.split('^');

        size_t k = 0;
        for (; k < descriptionList.size(); ++k)
        {
            descr.append(descriptionList.at(k));
            if (k != (descriptionList.size() - 1)) descr.append('\n');
        }
        quantity = QString::fromStdString(positionsList[i].getQuantity());
        issue = QString::fromStdString(positionsList[i].getIssue());

        QTableWidgetItem* positionIdItem = new QTableWidgetItem(QString::number(positionId));
        positionIdItem->setData(Qt::UserRole, positionId);
        QTableWidgetItem* descriptionItem = new QTableWidgetItem(descr);
        QTableWidgetItem* quantityItem = new QTableWidgetItem(quantity);
        QTableWidgetItem* issueItem = new QTableWidgetItem(issue);

        ui.positionsTableWidget->insertRow(i);
        ui.positionsTableWidget->setItem(i, 0, positionIdItem);
        ui.positionsTableWidget->setItem(i, 1, descriptionItem);
        ui.positionsTableWidget->setItem(i, 2, quantityItem);
        ui.positionsTableWidget->setItem(i, 3, issueItem);
    }

    ui.positionsTableWidget->resizeColumnsToContents();
    ui.positionsTableWidget->resizeRowsToContents();
    ui.positionsTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui.positionsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainForm::setClientCard(int orderId) 
{
    //заполняем карту клиента
    Order* order = findOrder(orderId);
    Client* client = findClient(order->getClient());

    ui.clientNameLineEdit->setText(QString::fromStdString(client->getName()));
    ui.clientPhoneLineEdit->setText(QString::fromStdString(client->getPhone()));
    ui.clientMailLineEdit->setText(QString::fromStdString(client->getMail()));
}

void MainForm::setRemark(int orderId) 
{
    //заполняем примечание
    Order* order = findOrder(orderId);
    QString remark;
    QString rmrk = QString::fromStdString(order->getRemark());
    QStringList remarkList = rmrk.split('^');

    size_t i = 0;
    for (; i < remarkList.size(); ++i)
    {
        remark.append(remarkList.at(i));
        if (i != (remarkList.size() - 1)) remark.append('\n');
    }

    ui.remarkTextEdit->setText(remark);
}

void MainForm::setChangesOrderCard(int orderId) 
{
    //заполняем таблицу изменений выделенного заказа

    clearChangesOrderCard();

    Order* order = findOrder(orderId);
    StaffAccount* createAccount(findAccount(order->getAccountCreate()));
    StaffAccount* editAccount(findAccount(order->getAccountEdit()));
    StaffAccount* availAccount(findAccount(order->getAccountAvailability()));

    ui.createDateLabel->setText(order->getDateTimeCreate().toString("dd.MM.yyyy"));
    ui.createTimeLabel->setText(order->getDateTimeCreate().toString("hh:mm"));
    ui.editDateLabel->setText(order->getDateTimeEdit().toString("dd.MM.yyyy"));
    ui.editTimeLabel->setText(order->getDateTimeEdit().toString("hh:mm"));
    ui.availDateLabel->setText(order->getDateTimeAvailability().toString("dd.MM.yyyy"));
    ui.availTimeLabel->setText(order->getDateTimeAvailability().toString("hh:mm"));

    if (createAccount->getId() && createAccount->getId() != -1)
    {
        ui.createLoginPositionLabel->setText(QString::fromStdString(createAccount->getPosition()));
        ui.createLoginNameLabel->setText(QString::fromStdString(createAccount->getName()));
    }

    if (editAccount->getId() && editAccount->getId() != -1)
    {
        ui.editLoginPositionLabel->setText(QString::fromStdString(editAccount->getPosition()));
        ui.editLoginNameLabel->setText(QString::fromStdString(editAccount->getName()));
    }

    if (availAccount->getId()&& availAccount->getId() != -1)
    {
        ui.availLoginPositionLabel->setText(QString::fromStdString(availAccount->getPosition()));
        ui.availLoginNameLabel->setText(QString::fromStdString(availAccount->getName()));
    }
}

void MainForm::clearChangesOrderCard() 
{
    //очищаеми карту изменений заказа

    ui.createDateLabel->clear();
    ui.createTimeLabel->clear();
    ui.editDateLabel->clear();
    ui.editTimeLabel->clear();
    ui.availDateLabel->clear();
    ui.availTimeLabel->clear();
    ui.createLoginPositionLabel->clear();
    ui.createLoginNameLabel->clear();
    ui.editLoginPositionLabel->clear();
    ui.editLoginNameLabel->clear();
    ui.availLoginPositionLabel->clear();
    ui.availLoginNameLabel->clear();
}

void MainForm::addClientSlot() 
{
    //открываем форму для добавления клиента в БД

    AddClientForm* add = new AddClientForm;
    add->setWindowModality(Qt::WindowModality::ApplicationModal);
    add->setAttribute(Qt::WA_DeleteOnClose);
    add->show();
}

void MainForm::clientListSlot() 
{
    // открываем форму для просмотра списка клиентов, полученных из бд

    ClientsForm* clientsForm = new ClientsForm;
    clientsForm->setWindowModality(Qt::WindowModality::ApplicationModal);
    clientsForm->setAttribute(Qt::WA_DeleteOnClose);
    clientsForm->show();
}

void MainForm::staffListSlot() 
{
    // открываем форму для просмотра списка сотрудников

    StaffsForm* staffsForm = new StaffsForm();
    staffsForm->setWindowModality(Qt::WindowModality::ApplicationModal);
    staffsForm->setAttribute(Qt::WA_DeleteOnClose);
    staffsForm->setWindowTitle("сотрудники");
    staffsForm->show();
}

void MainForm::createOrderSlot() 
{
    //открываем форму для создания заказа

    CreateOrderDialog createOrderDialog(this);
    createOrderDialog.setAccount(getAccount());
    createOrderDialog.saveBtn->setVisible(false);
    if (createOrderDialog.exec() && createOrderDialog._isOk)
    {   
        if (DataBase::addOrder(createOrderDialog.getNewOrder()))
        {
            createOrderDialog.getNewOrder().setId(DataBase::getLastId(DataBase::TABLE_ORDERS));
            _ordersList.push_back(std::move(createOrderDialog.getNewOrder()));
            setOrdersTableWidget();
            clearPositionsTableWidget();
            clearClientCard();
            clearChangesOrderCard();
        }            
        else
            QMessageBox::warning(0, "Error", "При добавлении заказа в БД возникла ошибка");
    }
}

void MainForm::printOrderSlot() 
{
    int orderId = -1;
    int currRow = ui.ordersTableWidget->currentRow();
    if (currRow != -1)
    {
        orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        Order* order = findOrder(orderId);
        //qDebug() << QString::fromStdString(getClient(getOrder(orderId).getClient()).getName());
    }
    
    setOrdersTableWidget();
    clearPositionsTableWidget();
    clearChangesOrderCard();
    clearClientCard();

    //auto it = std::find_if(_clientsList.begin(), _clientsList.end(), 2);
    
   
    //печать квитанции заказа
    //comming soon   
}



void MainForm::editOrderSlot() 
{
    //редактируем Заказ

    int currRow = ui.ordersTableWidget->currentRow();

    if (currRow != -1) 
    {
        int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        Order* order = findOrder(orderId);
        CreateOrderDialog createOrderDialog(this, order);
        createOrderDialog.setWindowTitle("Редактирование заказа");
        createOrderDialog.setAccount(getAccount());
        
        if (createOrderDialog.exec() && createOrderDialog._isOk)
        {
            if (DataBase::editOrder(createOrderDialog.getEditOrder()))
            {
                setOrdersTableWidget();
                clearPositionsTableWidget();
                clearClientCard();
                clearChangesOrderCard();
            }
            else
                QMessageBox::warning(0, "Error", "При сохранении заказа в БД возникла ошибка");
            
        }
    }
}

void MainForm::removeOrderSlot() 
{
    //удаляем Заказ

    int currRow = ui.ordersTableWidget->currentRow();

    if (currRow != -1) 
    {
        int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        Order* order = findOrder(orderId);
        if (DataBase::removeOrder(orderId))
        {
            _ordersList.erase(std::remove(_ordersList.begin(), _ordersList.end(), order), _ordersList.end());
            setOrdersTableWidget();
            clearPositionsTableWidget();
            clearClientCard();
            clearRemark();
            clearChangesOrderCard();
        }
    }
}

void MainForm::clickOnRowSlot()
{
    //нажатие на конкретный заказ

    int currRow = ui.ordersTableWidget->currentRow();
    int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
    setPositionsTableWidget(findOrder(orderId));
    setClientCard(orderId);
    setRemark(orderId);
    setChangesOrderCard(orderId);
}

void MainForm::searchOnClientSlot() 
{
    //поиск по клиенту

    QString searchClient = ui.searchLineEdit->text().toLower();
    std::vector<Order*> foundOrders;
    std::vector<Order>* allOrders = new std::vector<Order>(_ordersList);

    size_t i = 0;
    for (; i < allOrders->size(); ++i)
    {
        QString client = QString::fromStdString(findClient((*allOrders)[i].getClient())->getName());
        client = client.toLower();

        size_t k = 0;
        for (; k < searchClient.size(); ++k)
        {
            if (k == client.size()) break;
            if (searchClient.at(k) != client.at(k)) break;
            if (k == searchClient.size() - 1) 
            {
                foundOrders.push_back(findOrder((*allOrders)[i].getId()));
            }
        }
    }

    i = 0;
    for (; i < allOrders->size(); ++i)
    {
        //QString client = QString::fromStdString(findClient((*allOrders)[i].getClient()).getName());
        QString client = QString::fromStdString(findClient((*allOrders)[i].getClient())->getName());
        client = client.toLower();
        QStringList clientWordsList = client.split(" ");

        size_t n = 1;
        for (; n < clientWordsList.size(); ++n)
        {
            size_t k = 0;
            for (; k < searchClient.size(); ++k)
            {
                if (k == clientWordsList[n].size()) break;
                if (searchClient.at(k) != clientWordsList[n].at(k)) break;
                if (k == searchClient.size() - 1) 
                {
                    bool duplicateOrder = false;

                    size_t l = 0;
                    for (; l < foundOrders.size(); ++l)
                    {
                        if((*allOrders)[i].getId() == foundOrders[l]->getId()) duplicateOrder = true;
                    }

                    if(!duplicateOrder) foundOrders.push_back(std::move(findOrder((*allOrders)[i].getId())));
                }
            }
        }
    }
    
    delete allOrders;

    if (ui.searchLineEdit->text().isEmpty())
    {
        setOrdersTableWidget();
    }
    else
    {
        setOrdersTableWidget(foundOrders);
    }
    
    clearClientCard();
    clearRemark();
    clearChangesOrderCard();

}

void MainForm::slotCustomMenuRequested(const QPoint& pos) 
{
    //контекстное меню

    int row = ui.ordersTableWidget->selectionModel()->currentIndex().row();
    if (row != -1)
    {
        int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        Order* order(findOrder(orderId));
        QString newAvailability;
        if (order->getAvailability() == "Готово")
            newAvailability = "В работе";
        else
            newAvailability = "Готово";
        QMenu* menu = new QMenu(this);
        QAction* setAvailability = new QAction(newAvailability, this);
        connect(setAvailability, SIGNAL(triggered()), this, SLOT(slotSetAvailability()));
        menu->addAction(setAvailability);
        menu->popup(ui.ordersTableWidget->viewport()->mapToGlobal(pos));
    }
}

void MainForm::slotSetAvailability() 
{
    //устанавливаем "готово/в работе"

    QDateTime currDateTime = QDateTime::currentDateTime();
    int row = ui.ordersTableWidget->selectionModel()->currentIndex().row();
    if (row != -1) 
    {
        int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        Order* order = findOrder(orderId);

        if (order->getAvailability() == "В работе")
        {
            order->setAvailability("Готово");
        }
        else
        {
            order->setAvailability("В работе");
        }
        order->setAccountAvailability(getAccount().getId());
        order->setDateTimeAvailability(currDateTime);

        if (DataBase::editOrder(order))
        {
            //_ordersList[getIndex(_ordersList, orderId)] = order;
            setOrdersTableWidget();
            clearPositionsTableWidget();
            clearClientCard();
            clearRemark();
            clearChangesOrderCard();
        }
    }
}

Order* MainForm::findOrder(int orderId)
{
    auto it = std::find_if(_ordersList.begin(), _ordersList.end(), [&orderId](const Order& order) {return order.getId() == orderId; });
    return (it == _ordersList.end()) ? nullptr : &(*it);
}

Client* MainForm::findClient(int clientId)
{
    auto it = std::find_if(_clientsList.begin(), _clientsList.end(), [&clientId](const Client& client) {return client.getId() == clientId; });
    return (it == _clientsList.end()) ? nullptr : &(*it);
}
Staff* MainForm::findStaff(int staffId)
{
    auto it = std::find_if(_staffsList.begin(), _staffsList.end(), [&staffId](const Staff& staff) {return staff.getId() == staffId; });
    return (it == _staffsList.end()) ? nullptr : &(*it);
}

std::vector<OrderPosition> MainForm::findOrderPositions(int orderId)
{
    if (orderId != -1)
    {
        std::vector<OrderPosition> positionsOforder;
        for (auto position : _positionsList)
        {
            if (position.getIdOrder() == orderId)
                positionsOforder.push_back(std::move(position));
        }
        return positionsOforder;
    }
}

StaffAccount* MainForm::findAccount(int accountId)
{
    /*if (accountId != -1)
    {
        for (auto account : _accountsList)
        {
            if (account.getId() == accountId)
                return account;
        }
    }
    StaffAccount acc;
    acc.setId(-1);
    return acc;*/

    auto it = std::find_if(_accountsList.begin(), _accountsList.end(), [&accountId](const StaffAccount& account) {return account.getId() == accountId; });
    return (it == _accountsList.end()) ? nullptr : &(*it);
}

int MainForm::getIndex(const std::vector<Order>& ordersList, int orderId)
{
    for (int i = 0; i < ordersList.size(); ++i)
    {
        if (ordersList[i].getId() == orderId)
            return i;
    }
    return -1;
}

int MainForm::getIndex(const std::vector<Client>& clientsList, int clientId)
{
    for (int i = 0; i < clientsList.size(); ++i)
    {
        if (clientsList[i].getId() == clientId)
            return i;
    }
    return -1;
}

int MainForm::getIndex(const std::vector<Staff>& staffsList, int staffId)
{
    for (int i = 0; i < staffsList.size(); ++i)
    {
        if (staffsList[i].getId() == staffId)
            return i;
    }
    return -1;
}
