#include "MainForm.h"

std::vector<Order> MainForm::_ordersList;
std::vector<Client> MainForm::_clientsList;
std::vector<Staff> MainForm::_staffsList;
std::vector<OrderPosition> MainForm::_positionsList;
std::vector<StaffAccount> MainForm::_accountsList;

MainForm::MainForm(int accountId, QWidget* parent)
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
    _currentAccount = findAccount(accountId);
    setWindowTitle(windowTitle() + "  Учетная запись: " +
        QString::fromStdString(_currentAccount->getPosition()) + " " +
        QString::fromStdString(_currentAccount->getName()));
}

void MainForm::setOrdersTableWidget()
{
    ui.ordersTableWidget->clearContents();
    ui.ordersTableWidget->setRowCount(0);
    int orderId;
    QString date;
    QString payment;
    QString amount;
    QString availability;

    for (size_t i = 0; i < _ordersList.size(); ++i)
    {
        orderId = _ordersList[i].getId();
        date = _ordersList[i].getDate().toString("dd.MM.yyyy");
        payment = QString::fromStdString(_ordersList[i].getPayment());
        amount = QString::fromStdString(_ordersList[i].getAmount());
        availability = QString::fromStdString(_ordersList[i].getAvailability());

        QTableWidgetItem* orderIdItem = new QTableWidgetItem(QString::number(orderId));
        orderIdItem->setData(Qt::UserRole, orderId);
        QTableWidgetItem* clientItem = new QTableWidgetItem();
        QTableWidgetItem* managerItem = new QTableWidgetItem();
        QTableWidgetItem* designerItem = new QTableWidgetItem();

        if (const Client* client = findClient(_ordersList[i].getClient()))
        {
            clientItem->setText(QString::fromStdString(client->getName()));
            clientItem->setData(Qt::UserRole, client->getId());
        }

        if (const Staff* designer = findStaff(_ordersList[i].getDesigner()))
        {
            designerItem->setText(QString::fromStdString(designer->getName()));
            designerItem->setData(Qt::UserRole, designer->getId());
        }

        if (const Staff* manager = findStaff(_ordersList[i].getManager()))
        {
            if (manager->getId() > 0)
            {
                managerItem->setText(QString::fromStdString(manager->getName()));
                managerItem->setData(Qt::UserRole, manager->getId());
            }
        }

        ui.ordersTableWidget->insertRow(i);
        ui.ordersTableWidget->setItem(i, 0, orderIdItem);
        ui.ordersTableWidget->setItem(i, 1, new QTableWidgetItem(date));
        ui.ordersTableWidget->setItem(i, 2, clientItem);
        ui.ordersTableWidget->setItem(i, 3, new QTableWidgetItem(payment));
        ui.ordersTableWidget->setItem(i, 4, new QTableWidgetItem(amount));
        ui.ordersTableWidget->setItem(i, 5, managerItem);
        ui.ordersTableWidget->setItem(i, 6, designerItem);
        ui.ordersTableWidget->setItem(i, 7, new QTableWidgetItem(availability));
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
    QString payment;
    QString amount;
    QString availability;

    for (size_t i = 0; i < ordersList.size(); ++i)
    {
        orderId = ordersList[i]->getId();
        date = ordersList[i]->getDate().toString("dd.MM.yyyy");
        payment = QString::fromStdString(ordersList[i]->getPayment());
        amount = QString::fromStdString(ordersList[i]->getAmount());
        availability = QString::fromStdString(ordersList[i]->getAvailability());

        QTableWidgetItem* orderIdItem = new QTableWidgetItem(QString::number(orderId));
        orderIdItem->setData(Qt::UserRole, orderId);
        QTableWidgetItem* clientItem = new QTableWidgetItem();
        QTableWidgetItem* managerItem = new QTableWidgetItem();
        QTableWidgetItem* designerItem = new QTableWidgetItem();

        if (const Client* client = findClient(ordersList[i]->getClient()))
        {
            clientItem->setText(QString::fromStdString(client->getName()));
            clientItem->setData(Qt::UserRole, client->getId());
        }

        if (const Staff* designer = findStaff(ordersList[i]->getDesigner()))
        {
            designerItem->setText(QString::fromStdString(designer->getName()));
            designerItem->setData(Qt::UserRole, designer->getId());
        }

        if (const Staff* manager = findStaff(ordersList[i]->getManager()))
        {
            if (manager->getId() > 0)
            {
                managerItem->setText(QString::fromStdString(manager->getName()));
                managerItem->setData(Qt::UserRole, manager->getId());
            }
        }

        ui.ordersTableWidget->insertRow(i);
        ui.ordersTableWidget->setItem(i, 0, orderIdItem);
        ui.ordersTableWidget->setItem(i, 1, new QTableWidgetItem(date));
        ui.ordersTableWidget->setItem(i, 2, clientItem);
        ui.ordersTableWidget->setItem(i, 3, new QTableWidgetItem(payment));
        ui.ordersTableWidget->setItem(i, 4, new QTableWidgetItem(amount));
        ui.ordersTableWidget->setItem(i, 5, managerItem);
        ui.ordersTableWidget->setItem(i, 6, designerItem);
        ui.ordersTableWidget->setItem(i, 7, new QTableWidgetItem(availability));
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

StaffAccount* MainForm::findAccount(int accountId)
{
    auto it = std::find_if(_accountsList.begin(), _accountsList.end(), [&accountId](const StaffAccount& account) {return account.getId() == accountId; });
    return (it == _accountsList.end()) ? nullptr : &(*it);
}

std::vector<OrderPosition*> MainForm::findOrderPositions(int orderId)
{
    std::vector<OrderPosition*> positionsOfOrder;
    auto it = std::find_if(_positionsList.begin(), _positionsList.end(), [&orderId](const OrderPosition& position) {return position.getIdOrder() == orderId; });
    if (it != _positionsList.end()) positionsOfOrder.push_back(std::move(&(*it)));
    return positionsOfOrder;
}

OrderPosition* MainForm::findPosition(int positionId)
{
    auto it = std::find_if(_positionsList.begin(), _positionsList.end(), [&positionId](const OrderPosition& position) {return position.getIdPosition() == positionId; });
    return (it == _positionsList.end()) ? nullptr : &(*it);
}

bool MainForm::checkStaffInOrders(int staffId)
{
    auto it = std::find_if(_ordersList.begin(), _ordersList.end(), [&staffId](const Order& order) {return (order.getManager() == staffId) || (order.getDesigner() == staffId); });
    return (it == _ordersList.end()) ? false : true;
}

bool MainForm::checkClientInOrders(int clientId)
{
    auto it = std::find_if(_ordersList.begin(), _ordersList.end(), [&clientId](const Order& order) {return order.getClient() == clientId; });
    return (it == _ordersList.end()) ? false : true;
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

    for (size_t i = 0; i < positionsList.size(); ++i)
    {
        QString descr;
        positionId = positionsList[i].getIdPosition();
        description = QString::fromStdString(positionsList[i].getDescription());
        descriptionList = description.split('^');

        for (size_t k = 0; k < descriptionList.size(); ++k)
        {
            descr.append(descriptionList.at(k));
            if (k != (descriptionList.size() - 1)) 
                descr.append('\n');
        }
        quantity = QString::fromStdString(positionsList[i].getQuantity());
        issue = QString::fromStdString(positionsList[i].getIssue());

        QTableWidgetItem* positionIdItem = new QTableWidgetItem(QString::number(positionId));
        positionIdItem->setData(Qt::UserRole, positionId);

        ui.positionsTableWidget->insertRow(i);
        ui.positionsTableWidget->setItem(i, 0, positionIdItem);
        ui.positionsTableWidget->setItem(i, 1, new QTableWidgetItem(descr));
        ui.positionsTableWidget->setItem(i, 2, new QTableWidgetItem(quantity));
        ui.positionsTableWidget->setItem(i, 3, new QTableWidgetItem(issue));
    }

    ui.positionsTableWidget->resizeColumnsToContents();
    ui.positionsTableWidget->resizeRowsToContents();
    ui.positionsTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui.positionsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainForm::setClientCard(int orderId)
{
    //заполняем карту клиента
    const Order* order = findOrder(orderId);
    if (const Client* client = findClient(order->getClient()))
    {
        ui.clientNameLineEdit->setText(QString::fromStdString(client->getName()));
        ui.clientPhoneLineEdit->setText(QString::fromStdString(client->getPhone()));
        ui.clientMailLineEdit->setText(QString::fromStdString(client->getMail()));
    }
}

void MainForm::setRemark(int orderId)
{
    //заполняем примечание
    const Order* order = findOrder(orderId);
    QString remark;
    const QString rmrk = QString::fromStdString(order->getRemark());
    const QStringList remarkList = rmrk.split('^');

    for (size_t i = 0; i < remarkList.size(); ++i)
    {
        remark.append(remarkList.at(i));
        if (i != (remarkList.size() - 1)) 
            remark.append('\n');
    }

    ui.remarkTextEdit->setText(remark);
}

void MainForm::setChangesOrderCard(int orderId)
{
    //заполняем таблицу изменений выделенного заказа

    clearChangesOrderCard();

    if (const Order* order = findOrder(orderId))
    {
        if (const StaffAccount* createAccount = findAccount(order->getAccountCreate()))
        {
            ui.createLoginPositionLabel->setText(QString::fromStdString(createAccount->getPosition()));
            ui.createLoginNameLabel->setText(QString::fromStdString(createAccount->getName()));
        }

        if (const StaffAccount* editAccount = findAccount(order->getAccountEdit()))
        {
            ui.editLoginPositionLabel->setText(QString::fromStdString(editAccount->getPosition()));
            ui.editLoginNameLabel->setText(QString::fromStdString(editAccount->getName()));
        }

        if (const StaffAccount* availAccount = findAccount(order->getAccountAvailability()))
        {
            ui.availLoginPositionLabel->setText(QString::fromStdString(availAccount->getPosition()));
            ui.availLoginNameLabel->setText(QString::fromStdString(availAccount->getName()));
        }

        ui.createDateLabel->setText(order->getDateTimeCreate().toString("dd.MM.yyyy"));
        ui.createTimeLabel->setText(order->getDateTimeCreate().toString("hh:mm"));
        ui.editDateLabel->setText(order->getDateTimeEdit().toString("dd.MM.yyyy"));
        ui.editTimeLabel->setText(order->getDateTimeEdit().toString("hh:mm"));
        ui.availDateLabel->setText(order->getDateTimeAvailability().toString("dd.MM.yyyy"));
        ui.availTimeLabel->setText(order->getDateTimeAvailability().toString("hh:mm"));
    }
}

void MainForm::clearClientCard()
{
    ui.clientNameLineEdit->clear();
    ui.clientPhoneLineEdit->clear();
    ui.clientMailLineEdit->clear();
}

void MainForm::clearRemark()
{
    ui.remarkTextEdit->clear();
}

void MainForm::clearChangesOrderCard()
{
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

void MainForm::clientListSlot()
{
    // открываем форму для просмотра списка клиентов, полученных из бд

    ClientsFormDialog clientsForm;
    clientsForm.setWindowTitle("Список клиентов");
    clientsForm.setWindowModality(Qt::WindowModality::ApplicationModal);
    if (clientsForm.exec())
    {
        if (!ui.searchLineEdit->text().isEmpty())
            ui.searchLineEdit->clear();
        setOrdersTableWidget();
    }
    clearPositionsTableWidget();
    clearChangesOrderCard();
    clearClientCard();
    clearRemark();
}

void MainForm::staffListSlot()
{
    // открываем форму для просмотра списка сотрудников

    StaffsFormDialog staffsForm;
    staffsForm.setWindowModality(Qt::WindowModality::ApplicationModal);
    staffsForm.setWindowTitle("Список сотрудников");
    if (staffsForm.exec())
    {
        if (!ui.searchLineEdit->text().isEmpty())
            ui.searchLineEdit->clear();
        setOrdersTableWidget();
    }
    clearPositionsTableWidget();
    clearChangesOrderCard();
    clearClientCard();
    clearRemark();
}

void MainForm::createOrderSlot()
{
    //открываем форму для создания заказа

    CreateOrderDialog createOrderDialog(this);
    createOrderDialog.setWindowTitle("Создание нового заказа");
    createOrderDialog.setAccount(_currentAccount);
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
            clearRemark();
        }
        else
            QMessageBox::warning(0, "Error", "При добавлении заказа в БД возникла ошибка");
    }
}

void MainForm::editOrderSlot()
{
    //редактируем Заказ

    const int currRow = ui.ordersTableWidget->currentRow();

    if (currRow != -1)
    {
        const int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        Order* order = findOrder(orderId);
        CreateOrderDialog createOrderDialog(this, order);
        createOrderDialog.setWindowTitle("Редактирование заказа");
        createOrderDialog.setAccount(_currentAccount);

        if (createOrderDialog.exec() && createOrderDialog._isOk)
        {
            if (DataBase::editOrder(createOrderDialog.getEditOrder()))
            {
                ui.searchLineEdit->clear();
                setOrdersTableWidget();
                clearPositionsTableWidget();
                clearClientCard();
                clearChangesOrderCard();
                clearRemark();
            }
            else
                QMessageBox::warning(0, "Error", "При сохранении заказа в БД возникла ошибка");
        }
    }
}

void MainForm::removeOrderSlot()
{
    //удаляем Заказ

    const int currRow = ui.ordersTableWidget->currentRow();

    if (currRow != -1)
    {
        int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        if (DataBase::removeOrder(orderId))
        {
            auto itOrder = std::remove_if(MainForm::_ordersList.begin(), MainForm::_ordersList.end(), [&orderId](const Order& order) {return order.getId() == orderId; });
            MainForm::_ordersList.erase(itOrder, MainForm::_ordersList.end());
            auto itPosition = std::remove_if(MainForm::_positionsList.begin(), MainForm::_positionsList.end(), [&orderId](const OrderPosition& position) {return position.getIdOrder() == orderId; });
            MainForm::_positionsList.erase(itPosition, MainForm::_positionsList.end());
            setOrdersTableWidget();
            clearPositionsTableWidget();
            clearClientCard();
            clearRemark();
            clearChangesOrderCard();
        }
    }
}

void MainForm::printOrderSlot()
{
    //печать квитанции заказа
    int orderId = -1;
    const int currRow = ui.ordersTableWidget->currentRow();
    if (currRow != -1)
    {
        orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        if (const Order* order = findOrder(orderId))
        {
            PrintReceiptDialog printDialog(order);
            printDialog.setWindowTitle("Печать квитанции");
            printDialog.exec();
        }        
    }

    clearPositionsTableWidget();
    clearClientCard();
    clearRemark();
    clearChangesOrderCard();
}

void MainForm::clickOnRowSlot()
{
    //нажатие на конкретный заказ

    const int currRow = ui.ordersTableWidget->currentRow();
    const int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
    setPositionsTableWidget(findOrder(orderId));
    setClientCard(orderId);
    setRemark(orderId);
    setChangesOrderCard(orderId);
}

void MainForm::searchOnClientSlot()
{
    //поиск по клиенту

    const QString searchClient = ui.searchLineEdit->text().toLower();
    _foundOrders.clear();

    
    for (size_t i = 0; i < _ordersList.size(); ++i)
    {
        const QString client = QString::fromStdString(findClient(_ordersList[i].getClient())->getName()).toLower();

        for (size_t k = 0; k < searchClient.size(); ++k)
        {
            if (k == client.size()) break;
            if (searchClient.at(k) != client.at(k)) break;
            if (k == searchClient.size() - 1)
            {
                _foundOrders.push_back(findOrder(_ordersList[i].getId()));
            }
        }
    }

    for (size_t i = 0; i < _ordersList.size(); ++i)
    {
        const int orderId = _ordersList[i].getId();
        const QString client = QString::fromStdString(findClient(_ordersList[i].getClient())->getName()).toLower();
        const QStringList clientWordsList = client.split(" ");

        for (size_t n = 1; n < clientWordsList.size(); ++n)
        {
            
            for (size_t k = 0; k < searchClient.size(); ++k)
            {
                if (k == clientWordsList[n].size()) break;
                if (searchClient.at(k) != clientWordsList[n].at(k)) break;
                if (k == searchClient.size() - 1)
                {
                    bool duplicateOrder = false;

                    auto it = std::find_if(_foundOrders.begin(), _foundOrders.end(), [&orderId](const Order* order) {return order->getId() == orderId; });
                    duplicateOrder = (it == _foundOrders.end()) ? false : true;

                    if (!duplicateOrder) _foundOrders.push_back(std::move(findOrder(orderId)));
                }
            }
        }
    }

    (ui.searchLineEdit->text().isEmpty()) ? setOrdersTableWidget() : setOrdersTableWidget(_foundOrders);

    clearClientCard();
    clearRemark();
    clearChangesOrderCard();
}

void MainForm::slotCustomMenuRequested(const QPoint& pos)
{
    //контекстное меню

    const int row = ui.ordersTableWidget->selectionModel()->currentIndex().row();
    if (row != -1)
    {
        const int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        const Order* order(findOrder(orderId));
        QString newAvailability;
        if (order->getAvailability() == "Готово")
            newAvailability = "В работе";
        else
            newAvailability = "Готово";
        QMenu* menu = new QMenu(this);
        QAction* setAvailability = new QAction(newAvailability, this);
        QAction* editOrder = new QAction("Редактировать", this);
        QAction* removeOrder = new QAction("Удалить", this);
        connect(setAvailability, SIGNAL(triggered()), this, SLOT(slotSetAvailability()));
        connect(editOrder, SIGNAL(triggered()), this, SLOT(editOrderSlot()));
        connect(removeOrder, SIGNAL(triggered()), this, SLOT(removeOrderSlot()));
        menu->addAction(editOrder);
        menu->addAction(removeOrder);
        menu->addSeparator();
        menu->addAction(setAvailability);
        menu->popup(ui.ordersTableWidget->viewport()->mapToGlobal(pos));
    }
}

void MainForm::slotSetAvailability()
{
    //устанавливаем "готово/в работе"

    const int row = ui.ordersTableWidget->selectionModel()->currentIndex().row();
    if (row != -1)
    {
        const int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        Order* order = findOrder(orderId);

        if (order->getAvailability() == "В работе")
            order->setAvailability("Готово");
        else
            order->setAvailability("В работе");
        order->setAccountAvailability(_currentAccount->getId());
        order->setDateTimeAvailability(QDateTime::currentDateTime());

        if (DataBase::editOrder(order))
        {
            setOrdersTableWidget();
            clearPositionsTableWidget();
            clearClientCard();
            clearRemark();
            clearChangesOrderCard();
        }
    }
}