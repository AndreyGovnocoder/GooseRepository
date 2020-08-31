#include "MainForm.h"
#include "DataBase.h"
#include <QtWidgets\qmessagebox.h>
#include "StaffsForm.h"
#include "AddClientForm.h"
#include "ClientsForm.h"
#include "LoginPassDialog.h"
#include "CreateOrderDialog.h"

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
{    
    ui.setupUi(this);    
    connect(ui.ordersTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    ui.ordersTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    setOrdersTableWidget(DataBase::getOrdersList());
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

void MainForm::setOrdersTableWidget(const std::vector<Order>& ordersList) 
{
    ui.ordersTableWidget->clearContents();
    ui.ordersTableWidget->setRowCount(0);

    int orderId;
    QString date;
    QString client;
    int clientId;
    QString payment;
    QString amount;
    QString manager;
    int managerId;
    QString designer;
    int designerId;
    QString availability;

    for (int i = 0; i < ordersList.size(); ++i)
    {
        orderId = ordersList[i].getId();
        date = ordersList[i].getDate().toString("dd.MM.yyyy");
        client = QString::fromStdString(ordersList[i].getClient().getName());
        clientId = ordersList[i].getClient().getId();
        payment = QString::fromStdString(ordersList[i].getPayment());
        amount = QString::fromStdString(ordersList[i].getAmount());
        if (ordersList[i].getManager().getId() != NULL)
        {
            manager = QString::fromStdString(ordersList[i].getManager().getName());
            managerId = ordersList[i].getManager().getId();
        }

        if (ordersList[i].getDesigner().getId() != NULL)
        {
            designer = QString::fromStdString(ordersList[i].getDesigner().getName());
            designerId = ordersList[i].getDesigner().getId();
        }

        availability = QString::fromStdString(ordersList[i].getAvailability());
        QTableWidgetItem* orderIdItem = new QTableWidgetItem(QString::number(orderId));
        orderIdItem->setData(Qt::UserRole, orderId);
        QTableWidgetItem* dateItem = new QTableWidgetItem(date);
        QTableWidgetItem* clientItem = new QTableWidgetItem(client);
        clientItem->setData(Qt::UserRole, clientId);
        QTableWidgetItem* paymentItem = new QTableWidgetItem(payment);
        QTableWidgetItem* amountItem = new QTableWidgetItem(amount);
        QTableWidgetItem* managerItem = new QTableWidgetItem(manager);
        managerItem->setData(Qt::UserRole, managerId);
        QTableWidgetItem* designerItem = new QTableWidgetItem(designer);
        designerItem->setData(Qt::UserRole, designerId);
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

void MainForm::setPositionsTableWidget(int orderId) 
{
    //заполняем таблицу позиций выделенного заказа

    std::vector<OrderPosition> positionsList(DataBase::getOrderPositionsList(orderId));
    int positionId;
    QString description;
    QStringList descriptionList;
    QString quantity;
    QString issue;

    ui.positionsTableWidget->clearContents();
    ui.positionsTableWidget->setRowCount(0);
    ui.positionsTableWidget->hideColumn(0);

    for (int i = 0; i < positionsList.size(); ++i)
    {
        QString descr;
        positionId = positionsList[i].getIdPosition();
        description = QString::fromStdString(positionsList[i].getDescription());
        descriptionList = description.split('^');
        for (int i = 0; i < descriptionList.size(); ++i)
        {
            descr.append(descriptionList.at(i));
            if (i != (descriptionList.size() - 1)) descr.append('\n');
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
    
    Client client(DataBase::getOrder(orderId).getClient());

    ui.clientNameLineEdit->setText(QString::fromStdString(client.getName()));
    ui.clientPhoneLineEdit->setText(QString::fromStdString(client.getPhone()));
    ui.clientMailLineEdit->setText(QString::fromStdString(client.getMail()));
}

void MainForm::setRemark(int orderId) 
{
    //заполняем примечание
    
    QString remark;
    QString rmrk = QString::fromStdString(DataBase::getOrder(orderId).getRemark());
    QStringList remarkList = rmrk.split('^');
    for (int i = 0; i < remarkList.size(); ++i)
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

    Order order(DataBase::getOrder(orderId));
    StaffLogin createLogin(DataBase::getLogin(order.getLoginCreate()));
    StaffLogin editLogin(DataBase::getLogin(order.getLoginEdit()));
    StaffLogin availLogin(DataBase::getLogin(order.getLoginAvailability()));

    ui.createDateLabel->setText(order.getDateTimeCreate().toString("dd.MM.yyyy"));
    ui.createTimeLabel->setText(order.getDateTimeCreate().toString("hh:mm"));
    ui.editDateLabel->setText(order.getDateTimeEdit().toString("dd.MM.yyyy"));
    ui.editTimeLabel->setText(order.getDateTimeEdit().toString("hh:mm"));
    ui.availDateLabel->setText(order.getDateTimeAvailability().toString("dd.MM.yyyy"));
    ui.availTimeLabel->setText(order.getDateTimeAvailability().toString("hh:mm"));

    if (createLogin.getId() != 0 && createLogin.getId() != NULL) 
    {
        ui.createLoginPositionLabel->setText(QString::fromStdString(createLogin.getPosition()));
        ui.createLoginNameLabel->setText(QString::fromStdString(createLogin.getName()));
    }

    if (editLogin.getId() != 0 && editLogin.getId() != NULL) 
    {
        ui.editLoginPositionLabel->setText(QString::fromStdString(editLogin.getPosition()));
        ui.editLoginNameLabel->setText(QString::fromStdString(editLogin.getName()));
    }

    if (availLogin.getId() != 0 && availLogin.getId() != NULL) 
    {
        ui.availLoginPositionLabel->setText(QString::fromStdString(availLogin.getPosition()));
        ui.availLoginNameLabel->setText(QString::fromStdString(availLogin.getName()));
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
    createOrderDialog.setLogin(getLogin());
    if (createOrderDialog.exec())
    {
        setOrdersTableWidget(DataBase::getOrdersList());
        clearPositionsTableWidget();
    }
}

void MainForm::printOrderSlot() 
{
    setOrdersTableWidget(DataBase::getOrdersList());
    clearPositionsTableWidget();
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
        Order order = Order(DataBase::getOrder(orderId));
        CreateOrderDialog createOrderDialog(this);
        createOrderDialog.setWindowTitle("Редактирование заказа");
        createOrderDialog.dateEdit->setDate(order.getDate());
        if (order.getClient().getId() != 0) 
        {
            for (int i = 0; i <= createOrderDialog.clientsComboBox->count(); ++i)
            {
                if (order.getClient().getId() == createOrderDialog.clientsComboBox->itemData(i))
                {
                    createOrderDialog.clientsComboBox->setCurrentIndex(i);
                }
            }
        }
        else 
        {
            createOrderDialog.clientsComboBox->setCurrentIndex(-1);
        }

        for (int i = 0; i <= createOrderDialog.paymentComboBox->count(); ++i)
        {
            if (QString::fromStdString(order.getPayment()) == createOrderDialog.paymentComboBox->itemText(i))
            {
                createOrderDialog.paymentComboBox->setCurrentIndex(i);
            }
        }

        createOrderDialog.amountLineEdit->setText(QString::fromStdString(order.getAmount()));

        for (int i = 0; i <= createOrderDialog.managersComboBox->count(); ++i)
        {
            if (order.getManager().getId() == createOrderDialog.managersComboBox->itemData(i))
            {
                createOrderDialog.managersComboBox->setCurrentIndex(i);
            }
        }

        for (int i = 0; i <= createOrderDialog.designersComboBox->count(); ++i)
        {
            if (order.getDesigner().getId() == createOrderDialog.designersComboBox->itemData(i))
            {
                createOrderDialog.designersComboBox->setCurrentIndex(i);
            }
        }

        QString remarkString = QString::fromStdString(order.getRemark());
        QStringList remarkList = remarkString.split('^');
        QString remark;

        for (int i = 0; i < remarkList.size(); ++i)
        {
            remark.append(remarkList.at(i));
            if (i != (remarkList.size() - 1)) remark.append("\n");
        }

        createOrderDialog.remarkTextEdit->setText(remark);
        createOrderDialog.setIdEditOrder(order.getId());
        createOrderDialog.setPositionsList(order.getPositionsList());
        createOrderDialog.addOrderBtn->setVisible(false);
        
        if (createOrderDialog.exec())
        {
            setOrdersTableWidget(DataBase::getOrdersList());
            clearPositionsTableWidget();
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
        DataBase::removeOrder(orderId);
        setOrdersTableWidget(DataBase::getOrdersList());
        clearPositionsTableWidget();
        clearClientCard();
        clearRemark();
        clearChangesOrderCard();
    }
}

void MainForm::clickOnRowSlot()
{
    //нажатие на конкретный заказ

    int currRow = ui.ordersTableWidget->currentRow();
    int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
    setPositionsTableWidget(orderId);
    setClientCard(orderId);
    setRemark(orderId);
    setChangesOrderCard(orderId);
}

void MainForm::searchOnClientSlot() 
{
    //поиск по клиенту

    QString searchClient = ui.searchLineEdit->text().toLower();
    std::vector<Order> foundOrders;
    std::vector<Order>* allOrders = new std::vector<Order>(DataBase::getOrdersList());

    for (int i = 0; i < allOrders->size(); ++i)
    {
        QString client = QString::fromStdString((*allOrders)[i].getClient().getName());
        client = client.toLower();

        for (int k = 0; k < searchClient.size(); ++k)
        {
            if (k == client.size()) break;
            if (searchClient.at(k) != client.at(k)) break;
            if (k == searchClient.size() - 1) 
            {
                foundOrders.push_back(DataBase::getOrder((*allOrders)[i].getId()));
            }
        }
    }

    for (int i = 0; i < allOrders->size(); ++i)
    {
        QString client = QString::fromStdString((*allOrders)[i].getClient().getName());
        client = client.toLower();
        QStringList clientWordsList = client.split(" ");

        for (int n = 1; n < clientWordsList.size(); ++n)
        {

            for (int k = 0; k < searchClient.size(); ++k)
            {
                if (k == clientWordsList[n].size()) break;
                if (searchClient.at(k) != clientWordsList[n].at(k)) break;
                if (k == searchClient.size() - 1) 
                {
                    bool duplicateOrder = false;
                    for (int l = 0; l < foundOrders.size(); ++l)
                    {
                        if((*allOrders)[i].getId() == foundOrders[l].getId()) duplicateOrder = true;
                    }

                    if(!duplicateOrder) foundOrders.push_back(DataBase::getOrder((*allOrders)[i].getId()));
                }
            }
        }
    }
    
    delete allOrders;

    if (ui.searchLineEdit->text().isEmpty())
    {
        setOrdersTableWidget(DataBase::getOrdersList());
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
    int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    Order order(DataBase::getOrder(orderId));
    QString newAvailability;
    if (order.getAvailability() == "готово") 
        newAvailability = "в работе";
    else 
        newAvailability = "готово";    

    QMenu* menu = new QMenu(this);
    QAction* setAvailability = new QAction(newAvailability, this);
    connect(setAvailability, SIGNAL(triggered()), this, SLOT(slotSetAvailability()));
    menu->addAction(setAvailability);
    menu->popup(ui.ordersTableWidget->viewport()->mapToGlobal(pos));
}

void MainForm::slotSetAvailability() {
    //устанавливаем "готово/в работе"

    int row = ui.ordersTableWidget->selectionModel()->currentIndex().row();
    if (row >= 0) 
    {
        int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        DataBase::setAvailabilityOrder(orderId, getLogin().getId());
        setOrdersTableWidget(DataBase::getOrdersList());
        clearPositionsTableWidget();
        clearClientCard();
        clearRemark();
        clearChangesOrderCard();
    }
}