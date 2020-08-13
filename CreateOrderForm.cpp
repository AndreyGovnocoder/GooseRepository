#include "CreateOrderForm.h"
#include "SetDateDialog.h"
#include <qlistwidget.h>
#include "Client.h"
#include "DataBase.h"
#include "qmessagebox.h"
#include "Order.h"
#include "MainForm.h"
#include <qcompleter.h>

CreateOrderForm::CreateOrderForm(QTableWidget* ordersTableWidget, QTableWidget* positionsTableWidget, StaffLogin login,  QWidget *parent)
	: QWidget(parent)
{
	CreateOrderForm::ordersTableWidget = ordersTableWidget;
	CreateOrderForm::positionsTableWidget = positionsTableWidget;
	setupUi(this);
	CreateOrderForm::idEditOrder = -1;
	CreateOrderForm::setCurrentDate();
	CreateOrderForm::setClientsList();
	CreateOrderForm::setPayment();
	CreateOrderForm::setManagersList();
	CreateOrderForm::setDesignersList();
	CreateOrderForm::setIssueComboBox();
	CreateOrderForm::login = login;
}

CreateOrderForm::~CreateOrderForm(){}

void CreateOrderForm::setIdEditOrder(int idEditOrder) {
	CreateOrderForm::idEditOrder = idEditOrder;
}

void CreateOrderForm::setLogin(StaffLogin login) {
	CreateOrderForm::login = login;
}

StaffLogin CreateOrderForm::getLogin() {
	return CreateOrderForm::login;
}

void CreateOrderForm::setClientsList() {
	//устанавливаем список клиентов в comboBox

	std::vector<Client> clientsList(DataBase::getClientsList());
	for (int i = 0; i < clientsList.size(); i++) {
		QVariant var;
		var.setValue(clientsList[i].getId());

		clientsComboBox->addItem(QString::fromStdString(clientsList[i].getName()));
		clientsComboBox->setItemData(i, var);
	}

	clientsComboBox->setCurrentIndex(-1);	
}

void CreateOrderForm::setCurrentDate() {
	//устанавливаем текущую дату в dateEdit

	QDate date = QDate::currentDate();
	dateEdit->setDate(date);
}

void CreateOrderForm::setPayment() {
	//устанавливаем список "Оплаты"

	paymentComboBox->addItem("Оплачено");
	paymentComboBox->addItem("Не оплачено");
	paymentComboBox->addItem("50%");
	paymentComboBox->setCurrentIndex(-1);
}

void CreateOrderForm::setManagersList() {
	//устанавливаем список менеджеров

	std::vector<Staff> staffList(DataBase::getStaffList());
	int index = 0;
	for (int i = 0; i < staffList.size(); i++) {
		if (staffList[i].getPosition() == "менеджер") {
			QVariant var;
			var.setValue(staffList[i].getId());

			managersComboBox->addItem(QString::fromStdString(staffList[i].getName()));
			managersComboBox->setItemData(index, var);
			index++;
		}
	}

	managersComboBox->setCurrentIndex(-1);
}

void CreateOrderForm::setDesignersList() {
	//устанавливаем список дизайнеров

	std::vector<Staff> staffList(DataBase::getStaffList());
	int index = 0;
	for (int i = 0; i < staffList.size(); i++) {
		if (staffList[i].getPosition() == "дизайнер") {
			QVariant var;
			var.setValue(staffList[i].getId());

			designersComboBox->addItem(QString::fromStdString(staffList[i].getName()));
			designersComboBox->setItemData(index, var);
			index++;
		}
	}

	designersComboBox->setCurrentIndex(-1);
}

void CreateOrderForm::setIssueComboBox() {
	//устанавливаем список Выдачи

	issueComboBox->addItem("Цех");
	issueComboBox->addItem("Офис");
	issueComboBox->setCurrentIndex(-1);
}

void CreateOrderForm::addPosition() {
	//добавляем позицию заказа

	int rowCount = positionTableWidget->rowCount();
	QString description = descriptionTextEdit->toPlainText();
	QString quantity = quantityLineEdit->text();
	QString issue = issueComboBox->currentText();

	QTableWidgetItem* descriptionItem = new QTableWidgetItem(description);
	QTableWidgetItem* quantityItem = new QTableWidgetItem(quantity);
	QTableWidgetItem* issueItem = new QTableWidgetItem(issue);

	quantityItem->setTextAlignment(Qt::AlignCenter);
	issueItem->setTextAlignment(Qt::AlignCenter);

	positionTableWidget->insertRow(rowCount);
	positionTableWidget->setItem(rowCount, 0, descriptionItem);
	positionTableWidget->setItem(rowCount, 1, quantityItem);
	positionTableWidget->setItem(rowCount, 2, issueItem);
	positionTableWidget->resizeColumnsToContents();
	positionTableWidget->resizeRowsToContents();
	positionTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	positionTableWidget->horizontalHeaderItem(2)->setTextAlignment(50);
	positionTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	positionTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	positionTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void CreateOrderForm::setPositionsList(std::vector<OrderPosition> positionsList) {
	//добавляем в таблицу список позиций заказа

	for (int i = 0; i < positionsList.size(); i++) {
		QString description;
		QString descr;
		QStringList descriptionList;
		description = QString::fromStdString(positionsList[i].getDescription());
		descriptionList = description.split('^');

		for (int i = 0; i < descriptionList.size(); i++) {
			descr.append(descriptionList.at(i));
			if (i != (descriptionList.size() - 1)) descr.append('\n');
		}

		QString quantity = positionsList[i].getQQuantity();
		QString issue = positionsList[i].getQIssue();

		QTableWidgetItem* descriptionItem = new QTableWidgetItem(descr);
		QTableWidgetItem* quantityItem = new QTableWidgetItem(quantity);
		QTableWidgetItem* issueItem = new QTableWidgetItem(issue);

		positionTableWidget->insertRow(i);
		positionTableWidget->setItem(i, 0, descriptionItem);
		positionTableWidget->setItem(i, 1, quantityItem);
		positionTableWidget->setItem(i, 2, issueItem);
	}

	positionTableWidget->resizeColumnsToContents();
	positionTableWidget->resizeRowsToContents();
	positionTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	positionTableWidget->horizontalHeaderItem(2)->setTextAlignment(50);
	positionTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	positionTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	positionTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

std::vector<OrderPosition> CreateOrderForm::getPositionsList() {
	//получаем список позиций заказа

	std::vector<OrderPosition> positionsList;
	int lastIdPosition = DataBase::getLastId(DataBase::getTableOrderPositions()) + 1;

	for (int i = 0; i < positionTableWidget->rowCount(); i++) {
		OrderPosition position;
		std::string quantity = positionTableWidget->item(i, 1)->text().toStdString();
		std::string issue = positionTableWidget->item(i, 2)->text().toStdString();

		position.setIdPosition(lastIdPosition + i);

		if (idEditOrder == -1) {
			position.setIdOrder(DataBase::getLastId(DataBase::getTableOrders()) + 1);
		}
		else {
			position.setIdOrder(idEditOrder);
		}
		position.setQuantity(quantity);
		position.setIssue(issue);

		QString description = positionTableWidget->item(i, 0)->text();
		QStringList descList = description.split('\n');
		std::string descrString;

		for (int i = 0; i < descList.size(); i++) {
			descrString.append(descList.at(i).toStdString());
			if (i != (descList.size() - 1)) descrString.append("^");
		}

		position.setDescription(descrString);

		positionsList.push_back(position);
	}

	return positionsList;
}

QString CreateOrderForm::getRemark() {
	// получаем примечание

	QString remarkString = remarkTextEdit->toPlainText();
	QStringList remarkList = remarkString.split('\n');
	QString remark;

	for (int i = 0; i < remarkList.size(); i++) {
		remark.append(remarkList.at(i));
		if (i != (remarkList.size() - 1)) remark.append("^");
	}

	return remark;
}

Order CreateOrderForm::getOrder() {
	// получаем данные заказа

	Order order;
	QDateTime currentDateTime = QDateTime::currentDateTime();

	if (idEditOrder == -1) {
		order.setId(DataBase::getLastId(DataBase::getTableOrders()) + 1);
		order.setLoginCreate(getLogin().getId());
		order.setLoginEdit(0);
		order.setLoginAvailability(0);
		order.setDateTimeCreate(currentDateTime);
	}
	else {
		order.setId(idEditOrder);
		order.setLoginEdit(getLogin().getId());
		order.setLoginCreate(DataBase::getOrder(order.getId()).getLoginCreate());
		order.setLoginAvailability(DataBase::getOrder(order.getId()).getLoginAvailability());
		order.setDateTimeEdit(currentDateTime);
		order.setDateTimeCreate(DataBase::getOrder(order.getId()).getDateTimeCreate());
		order.setDateTimeAvailability(DataBase::getOrder(order.getId()).getDateTimeAvailability());
	}

	order.setDate(dateEdit->date());
	order.setAmount(amountLineEdit->text().toStdString());
	order.setPayment(paymentComboBox->currentText().toStdString());
	order.setAvailability("в работе");
	order.setRemark(getRemark().toStdString());

	int managerId = 0;
	int designerId = 0;
	int clientId = 0;


	if (managersComboBox->currentIndex() != -1) {
		managerId = managersComboBox->currentData().toInt();
		for (int i = 0; i < DataBase::getStaffList().size(); i++) {
			if (DataBase::getStaffList()[i].getId() == managerId) {
				order.setManager(DataBase::getStaffList()[i]);
				break;
			}
		}
	}
	else {
		QMessageBox::information(this, "Title", "не выбран менеджер");
		order.setManager(Staff(0));
	}

	if (designersComboBox->currentIndex() != -1) {
		designerId = designersComboBox->currentData().toInt();
		for (int i = 0; i < DataBase::getStaffList().size(); i++) {
			if (DataBase::getStaffList()[i].getId() == designerId) {
				order.setDesigner(DataBase::getStaffList()[i]);
				break;
			}
		}
	}
	else {
		QMessageBox::information(this, "Title", "не выбран дизайнер");
		order.setDesigner(Staff(0));
	}

	if (clientsComboBox->currentIndex() != -1) {
		clientId = clientsComboBox->currentData().toInt();
		for (int i = 0; i < DataBase::getClientsList().size(); i++) {
			if (DataBase::getClientsList()[i].getId() == clientId) {
				order.setClient(DataBase::getClientsList()[i]);
				break;
			}
		}
	}
	else {
		QMessageBox::information(this, "Title", "не выбран клиент");
		order.setClient(Client(0, "", "", ""));
	}

	std::vector<OrderPosition> positionsList(getPositionsList());
	order.setPositionsList(positionsList);

	return order;
}

void CreateOrderForm::slot1() {
	//открыть календарь для установки даты

	SetDateDialog setDateDialog(dateEdit->date());
	setDateDialog.calendarWidget->setSelectedDate(dateEdit->date());
	QPoint point = QCursor::pos();
	point.setX(point.x() - setDateDialog.width() / 2);
	point.setY(point.y() - setDateDialog.height() / 2);
	setDateDialog.move(point);
	setDateDialog.setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	if (setDateDialog.exec()) {
		dateEdit->setDate(setDateDialog.calendarWidget->selectedDate());
	}
}

void CreateOrderForm::slot2() {
	//внести заказ в БД

	Order* order = new Order(getOrder());
	DataBase::addOrder(order);
	MainForm::setOrdersTableWidget(CreateOrderForm::ordersTableWidget, new std::vector<Order>(DataBase::getOrdersList()));
	MainForm::clearPositionsTableWidget(CreateOrderForm::positionsTableWidget);
	QWidget::close();
}

void CreateOrderForm::slot3() {
	//добавить позицию

	addPosition();
	descriptionTextEdit->clear();
	quantityLineEdit->clear();
	issueComboBox->setCurrentIndex(-1);
}

void CreateOrderForm::slot4() {
	//удаляем позицию заказа

	int currRow = positionTableWidget->currentRow();
	positionTableWidget->removeRow(currRow);
}

void CreateOrderForm::slot5() {
	//сохраняем изменения

	Order* order = new Order(getOrder());
	DataBase::editOrder(order);
	MainForm::setOrdersTableWidget(CreateOrderForm::ordersTableWidget, new std::vector<Order>(DataBase::getOrdersList()));
	MainForm::clearPositionsTableWidget(CreateOrderForm::positionsTableWidget);
	QWidget::close();
}


