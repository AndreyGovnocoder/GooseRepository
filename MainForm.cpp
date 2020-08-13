#include "MainForm.h"
#include "DataBase.h"
#include <QtWidgets\qmessagebox.h>
#include "CreateOrderForm.h"
#include "StaffsForm.h"
#include "AddClientForm.h"
#include "ClientsForm.h"
#include "LoginPassDialog.h"

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
{    
    ui.setupUi(this);    
    connect(ui.ordersTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    ui.ordersTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    MainForm::setOrdersTableWidget(ui.ordersTableWidget, new std::vector<Order>(DataBase::getOrdersList()));
    MainForm::setTransparentClientCard();  
}

void MainForm::setLogin(StaffLogin login) {
    MainForm::login = login;
}

StaffLogin MainForm::getLogin() {
    return MainForm::login;
}


void MainForm::setTransparentClientCard() {
    //делаем поля карты клиенты прозрачными 

    QPalette palette = ui.clientNameLineEdit->palette();

    palette.setColor(QPalette::Active, QPalette::Base, Qt::transparent);
    palette.setColor(QPalette::Inactive, QPalette::Base, Qt::transparent);

    ui.clientNameLineEdit->setPalette(palette);
    ui.clientPhoneLineEdit->setPalette(palette);
    ui.clientMailLineEdit->setPalette(palette);
}

void MainForm::clearPositionsTableWidget(QTableWidget* positionsTableWidget) {
    //очищаем таблицу позиций заказа

    positionsTableWidget->clearContents();
    positionsTableWidget->setRowCount(0);
}

void MainForm::clearClientCard() {
    //очищаем карту клиента

    ui.clientNameLineEdit->clear();
    ui.clientPhoneLineEdit->clear();
    ui.clientMailLineEdit->clear();
}

void MainForm::clearRemark() {
    //очищаем примечание

    ui.remarkTextEdit->clear();
}

void MainForm::setOrdersTableWidget(QTableWidget* ordersTableWidget, std::vector<Order>* ordersList) {
    //заполняем таблицу заказов данными

    ordersTableWidget->clearContents();
    ordersTableWidget->setRowCount(0);
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

    for (int i = 0; i < ordersList->size(); i++) {
        orderId = (*ordersList)[i].getId();
        date = (*ordersList)[i].getDate().toString("dd.MM.yyyy");
        client = (*ordersList)[i].getClient().getQName();
        clientId = (*ordersList)[i].getClient().getId();
        payment = (*ordersList)[i].getQPayment();
        amount = (*ordersList)[i].getQAmount();
        if ((*ordersList)[i].getManager().getId() != NULL) {
            manager = (*ordersList)[i].getManager().getQName();
            managerId = (*ordersList)[i].getManager().getId();
        }

        if ((*ordersList)[i].getDesigner().getId() != NULL) {
            designer = (*ordersList)[i].getDesigner().getQName();
            designerId = (*ordersList)[i].getDesigner().getId();
        }

        availability = (*ordersList)[i].getQAvailability();
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

        ordersTableWidget->insertRow(i);
        ordersTableWidget->setItem(i, 0, orderIdItem);
        ordersTableWidget->setItem(i, 1, dateItem);
        ordersTableWidget->setItem(i, 2, clientItem);
        ordersTableWidget->setItem(i, 3, paymentItem);
        ordersTableWidget->setItem(i, 4, amountItem);
        ordersTableWidget->setItem(i, 5, managerItem);
        ordersTableWidget->setItem(i, 6, designerItem);
        ordersTableWidget->setItem(i, 7, availabilityItem);
    }

    ordersTableWidget->hideColumn(0);
    ordersTableWidget->resizeColumnsToContents();
    ordersTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ordersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    delete ordersList;   
}

void MainForm::setPositionsTableWidget(int orderId) {
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

    for (int i = 0; i < positionsList.size(); i++) {
        QString descr;
        positionId = positionsList[i].getIdPosition();
        description = positionsList[i].getQDescription();
        descriptionList = description.split('^');
        for (int i = 0; i < descriptionList.size(); i++) {
            descr.append(descriptionList.at(i));
            if (i != (descriptionList.size() - 1)) descr.append('\n');
        }
        quantity = positionsList[i].getQQuantity();
        issue = positionsList[i].getQIssue();

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

void MainForm::setClientCard(int orderId) {
    //заполняем карту клиента

    Order* order = new Order(DataBase::getOrder(orderId));
    Client client;
    client.setId(order->getClient().getId());
    client.setName(order->getClient().getName());
    client.setPhone(order->getClient().getPhone());
    client.setMail(order->getClient().getMail());

    ui.clientNameLineEdit->setText(client.getQName());
    ui.clientPhoneLineEdit->setText(client.getQPhone());
    ui.clientMailLineEdit->setText(client.getQMail());

    delete order;
}

void MainForm::setRemark(int orderId) {
    //заполняем примечание

    Order* order = new Order(DataBase::getOrder(orderId));
    QString remark;
    QString rmrk = QString::fromStdString(order->getRemark());
    QStringList remarkList = rmrk.split('^');
    for (int i = 0; i < remarkList.size(); i++) {
        remark.append(remarkList.at(i));
        if (i != (remarkList.size() - 1)) remark.append('\n');
    }

    ui.remarkTextEdit->setText(remark);
}

void MainForm::setChangesOrderCard(int orderId) {
    //заполняем таблицу изменений выделенного заказа

    clearChangesOrderCard();

    Order* order = new Order(DataBase::getOrder(orderId));
    StaffLogin* createLogin = new StaffLogin(DataBase::getLogin(order->getLoginCreate()));
    StaffLogin* editLogin = new StaffLogin(DataBase::getLogin(order->getLoginEdit()));
    StaffLogin* availLogin = new StaffLogin(DataBase::getLogin(order->getLoginAvailability()));

    ui.createDateLabel->setText(order->getDateTimeCreate().toString("dd.MM.yyyy"));
    ui.createTimeLabel->setText(order->getDateTimeCreate().toString("hh:mm"));
    ui.editDateLabel->setText(order->getDateTimeEdit().toString("dd.MM.yyyy"));
    ui.editTimeLabel->setText(order->getDateTimeEdit().toString("hh:mm"));
    ui.availDateLabel->setText(order->getDateTimeAvailability().toString("dd.MM.yyyy"));
    ui.availTimeLabel->setText(order->getDateTimeAvailability().toString("hh:mm"));

    if (createLogin->getId() != 0 && createLogin->getId() != NULL) {
        ui.createLoginPositionLabel->setText(createLogin->getQPosition());
        ui.createLoginNameLabel->setText(createLogin->getQName());
    }

    if (editLogin->getId() != 0 && editLogin->getId() != NULL) {
        ui.editLoginPositionLabel->setText(editLogin->getQPosition());
        ui.editLoginNameLabel->setText(editLogin->getQName());
    }

    if (availLogin->getId() != 0 && availLogin->getId() != NULL) {
        ui.availLoginPositionLabel->setText(availLogin->getQPosition());
        ui.availLoginNameLabel->setText(availLogin->getQName());
    }
}

void MainForm::clearChangesOrderCard() {
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

void MainForm::slot1() {
    //открываем форму для добавления клиента в БД

    AddClientForm* add = new AddClientForm;
    add->setWindowModality(Qt::WindowModality::ApplicationModal);
    add->show();
}

void MainForm::slot2() {
    // открываем форму для просмотра списка клиентов, полученных из бд

    ClientsForm* get = new ClientsForm;
    get->setWindowModality(Qt::WindowModality::ApplicationModal);
    get->show();
}

void MainForm::slot3() {
    // открываем форму для просмотра списка сотрудников

    StaffsForm* staff = new StaffsForm();
    staff->setWindowModality(Qt::WindowModality::ApplicationModal);
    staff->setWindowTitle("сотрудники");
    staff->show();
}

void MainForm::slot4() {
    //открываем форму для создания заказа

    CreateOrderForm* createOrder = new CreateOrderForm(ui.ordersTableWidget, ui.positionsTableWidget, getLogin());
    createOrder->setWindowModality(Qt::WindowModality::ApplicationModal);
    createOrder->setWindowTitle("Создание нового заказа");
    createOrder->saveBtn->setVisible(false);
    createOrder->show();
}

void MainForm::slot5() {
    //печать квитанции заказа

    //comming soon   
}

void MainForm::slot6() {
    //редактируем Заказ

    int currRow = ui.ordersTableWidget->currentRow();

    if (currRow != -1) {
        int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        Order* order = new Order(DataBase::getOrder(orderId));
        CreateOrderForm *createOrder = new CreateOrderForm(ui.ordersTableWidget, ui.positionsTableWidget, getLogin());
        createOrder->setWindowModality(Qt::WindowModality::ApplicationModal);
        createOrder->setWindowTitle("Редактирование заказа");
        createOrder->dateEdit->setDate(order->getDate());
        if (order->getClient().getId() != 0) {
            for (int i = 0; i <= createOrder->clientsComboBox->count(); i++) {
                if (order->getClient().getId() == createOrder->clientsComboBox->itemData(i)) {
                    createOrder->clientsComboBox->setCurrentIndex(i);
                }
            }
        }
        else {
            createOrder->clientsComboBox->setCurrentIndex(-1);
        }

        for (int i = 0; i <= createOrder->paymentComboBox->count(); i++) {
            if (order->getQPayment() == createOrder->paymentComboBox->itemText(i)) {
                createOrder->paymentComboBox->setCurrentIndex(i);
            }
        }

        createOrder->amountLineEdit->setText(order->getQAmount());

        for (int i = 0; i <= createOrder->managersComboBox->count(); i++) {
            if (order->getManager().getId() == createOrder->managersComboBox->itemData(i)) {
                createOrder->managersComboBox->setCurrentIndex(i);
            }
        }

        for (int i = 0; i <= createOrder->designersComboBox->count(); i++) {
            if (order->getDesigner().getId() == createOrder->designersComboBox->itemData(i)) {
                createOrder->designersComboBox->setCurrentIndex(i);
            }
        }

        QString remarkString = QString::fromStdString(order->getRemark());
        QStringList remarkList = remarkString.split('^');
        QString remark;

        for (int i = 0; i < remarkList.size(); i++) {
            remark.append(remarkList.at(i));
            if (i != (remarkList.size() - 1)) remark.append("\n");
        }

        createOrder->remarkTextEdit->setText(remark);
        createOrder->setIdEditOrder(order->getId());
        createOrder->setPositionsList(order->getPositionsList());
        createOrder->addOrderBtn->setVisible(false);
        createOrder->show();
    }
}

void MainForm::slot7() {
    //удаляем Заказ

    int currRow = ui.ordersTableWidget->currentRow();

    if (currRow != -1) {
        int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
        DataBase::removeOrder(orderId);
        MainForm::setOrdersTableWidget(ui.ordersTableWidget, new std::vector<Order>(DataBase::getOrdersList()));
        MainForm::clearPositionsTableWidget(ui.positionsTableWidget);
        MainForm::clearClientCard();
        MainForm::clearRemark();
        MainForm::clearChangesOrderCard();
    }
}

void MainForm::slot8() {
    //нажатие на конкретный заказ

    int currRow = ui.ordersTableWidget->currentRow();
    int orderId = ui.ordersTableWidget->item(currRow, 0)->data(Qt::UserRole).toInt();
    MainForm::setPositionsTableWidget(orderId);
    setClientCard(orderId);
    setRemark(orderId);
    setChangesOrderCard(orderId);
    Order order(DataBase::getOrder(orderId));
    ui.label->setText(QString::number(order.getLoginEdit()));
}

void MainForm::slot9() {
    //поиск по клиенту

    QString searchClient = ui.searchLineEdit->text().toLower();
    std::vector<Order>* foundOrders = new std::vector<Order>;
    std::vector<Order>* allOrders = new std::vector<Order>(DataBase::getOrdersList());

    for (int i = 0; i < allOrders->size(); i++) {
        QString client = (*allOrders)[i].getClient().getQName().toLower();

        for (int k = 0; k < searchClient.size(); k++) {
            if (k == client.size()) break;
            if (searchClient.at(k) != client.at(k)) break;
            if (k == searchClient.size() - 1) {
                foundOrders->push_back(DataBase::getOrder((*allOrders)[i].getId()));
            }
        }
    }

    for (int i = 0; i < allOrders->size(); i++) {
        QString client = (*allOrders)[i].getClient().getQName().toLower();
        QStringList clientWordsList = client.split(" ");

        for (int n = 1; n < clientWordsList.size(); n++) {

            for (int k = 0; k < searchClient.size(); k++) {
                if (k == clientWordsList[n].size()) break;
                if (searchClient.at(k) != clientWordsList[n].at(k)) break;
                if (k == searchClient.size() - 1) {
                    bool duplicateOrder = false;
                    for (int l = 0; l < foundOrders->size(); l++) {
                        if((*allOrders)[i].getId() == (*foundOrders)[l].getId()) duplicateOrder = true;
                    }

                    if(!duplicateOrder) foundOrders->push_back(DataBase::getOrder((*allOrders)[i].getId()));
                }
            }
        }
    }
    
    delete allOrders;
    if(ui.searchLineEdit->text().isEmpty()) MainForm::setOrdersTableWidget(ui.ordersTableWidget, new std::vector<Order>(DataBase::getOrdersList()));
    else MainForm::setOrdersTableWidget(ui.ordersTableWidget, foundOrders); 
    
    MainForm::clearClientCard();
    MainForm::clearRemark();
    MainForm::clearChangesOrderCard();

}

void MainForm::slotCustomMenuRequested(QPoint pos) {
    //контекстное меню

    int row = ui.ordersTableWidget->selectionModel()->currentIndex().row();
    int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    Order* order = new Order(DataBase::getOrder(orderId));
    QString newAvailability;
    if (order->getAvailability() == "готово") 
        newAvailability = "в работе";
    else 
        newAvailability = "готово";    

    QMenu* menu = new QMenu(this);
    QAction* setAvailability = new QAction(newAvailability, this);
    connect(setAvailability, SIGNAL(triggered()), this, SLOT(slotSetAvailability()));
    menu->addAction(setAvailability);
    menu->popup(ui.ordersTableWidget->viewport()->mapToGlobal(pos));

    delete order;
}

void MainForm::slotSetAvailability() {
    //устанавливаем "готово/в работе"

    int row = ui.ordersTableWidget->selectionModel()->currentIndex().row();
    if (row >= 0) {
        int orderId = ui.ordersTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        DataBase::setAvailabilityOrder(orderId, getLogin().getId());
        MainForm::setOrdersTableWidget(ui.ordersTableWidget, new std::vector<Order>(DataBase::getOrdersList()));
        MainForm::clearPositionsTableWidget(ui.positionsTableWidget);
        MainForm::clearClientCard();
        MainForm::clearRemark();
        MainForm::clearChangesOrderCard();
    }
}