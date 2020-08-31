#include "CreateOrderDialog.h"
#include "SetDateDialog.h"
#include "Client.h"
#include "DataBase.h"
#include "qmessagebox.h"
#include "Order.h"
#include "MainForm.h"
#include <qcompleter.h>

CreateOrderDialog::CreateOrderDialog(QWidget* parent)
	: QDialog(parent)
{
		setupUi(this);
		_idEditOrder = -1;
		setCurrentDate();
		setClientsList();
		setPayment();
		setManagersList();
		setDesignersList();
		setIssueComboBox();
}

void CreateOrderDialog::setClientsList()
{
	//устанавливаем список клиентов в comboBox

	std::vector<Client> clientsList(DataBase::getClientsList());
	for (int i = 0; i < clientsList.size(); ++i)
	{
		QVariant var;
		var.setValue(clientsList[i].getId());

		clientsComboBox->addItem(QString::fromStdString(clientsList[i].getName()));
		clientsComboBox->setItemData(i, var);
	}

	clientsComboBox->setCurrentIndex(-1);
}

void CreateOrderDialog::setCurrentDate()
{
	//устанавливаем текущую дату в dateEdit

	QDate date = QDate::currentDate();
	dateEdit->setDate(date);
}

void CreateOrderDialog::setPayment()
{
	//устанавливаем список "Оплаты"

	paymentComboBox->addItem("Оплачено");
	paymentComboBox->addItem("Не оплачено");
	paymentComboBox->addItem("50%");
	paymentComboBox->setCurrentIndex(-1);
}

void CreateOrderDialog::setManagersList()
{
	//устанавливаем список менеджеров

	std::vector<Staff> staffList(DataBase::getStaffList());
	int index = 0;
	for (int i = 0; i < staffList.size(); ++i)
	{
		if (staffList[i].getPosition() == "менеджер")
		{
			QVariant var;
			var.setValue(staffList[i].getId());

			managersComboBox->addItem(QString::fromStdString(staffList[i].getName()));
			managersComboBox->setItemData(index, var);
			++index;
		}
	}

	managersComboBox->setCurrentIndex(-1);
}

void CreateOrderDialog::setDesignersList()
{
	//устанавливаем список дизайнеров

	std::vector<Staff> staffList(DataBase::getStaffList());
	int index = 0;
	for (int i = 0; i < staffList.size(); ++i)
	{
		if (staffList[i].getPosition() == "дизайнер")
		{
			QVariant var;
			var.setValue(staffList[i].getId());

			designersComboBox->addItem(QString::fromStdString(staffList[i].getName()));
			designersComboBox->setItemData(index, var);
			++index;
		}
	}

	designersComboBox->setCurrentIndex(-1);
}

void CreateOrderDialog::setIssueComboBox()
{
	//устанавливаем список Выдачи

	issueComboBox->addItem("Цех");
	issueComboBox->addItem("Офис");
	issueComboBox->setCurrentIndex(-1);
}

void CreateOrderDialog::addPosition()
{
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

void CreateOrderDialog::setPositionsList(const std::vector<OrderPosition>& positionsList)
{
	//добавляем в таблицу список позиций заказа

	for (int i = 0; i < positionsList.size(); ++i)
	{
		QString description;
		QString descr;
		QStringList descriptionList;
		description = QString::fromStdString(positionsList[i].getDescription());
		descriptionList = description.split('^');

		for (int i = 0; i < descriptionList.size(); ++i)
		{
			descr.append(descriptionList.at(i));
			if (i != (descriptionList.size() - 1)) descr.append('\n');
		}

		QString quantity = QString::fromStdString(positionsList[i].getQuantity());
		QString issue = QString::fromStdString(positionsList[i].getIssue());

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

std::vector<OrderPosition> CreateOrderDialog::getPositionsList()
{
	//получаем список позиций заказа

	std::vector<OrderPosition> positionsList;
	int lastIdPosition = DataBase::getLastId(DataBase::getTableOrderPositions()) + 1;

	for (int i = 0; i < positionTableWidget->rowCount(); ++i)
	{
		OrderPosition position;
		std::string quantity = positionTableWidget->item(i, 1)->text().toStdString();
		std::string issue = positionTableWidget->item(i, 2)->text().toStdString();

		position.setIdPosition(lastIdPosition + i);

		if (_idEditOrder == -1)
		{
			position.setIdOrder(DataBase::getLastId(DataBase::getTableOrders()) + 1);
		}
		else
		{
			position.setIdOrder(_idEditOrder);
		}
		position.setQuantity(quantity);
		position.setIssue(issue);

		QString description = positionTableWidget->item(i, 0)->text();
		QStringList descList = description.split('\n');
		std::string descrString;

		for (int i = 0; i < descList.size(); ++i)
		{
			descrString.append(descList.at(i).toStdString());
			if (i != (descList.size() - 1)) descrString.append("^");
		}

		position.setDescription(descrString);

		positionsList.push_back(position);
	}

	return positionsList;
}

std::string CreateOrderDialog::getRemark()
{
	// получаем примечание

	QString remarkString = remarkTextEdit->toPlainText();
	QStringList remarkList = remarkString.split('\n');
	QString remark;

	for (int i = 0; i < remarkList.size(); ++i)
	{
		remark.append(remarkList.at(i));
		if (i != (remarkList.size() - 1)) remark.append("^");
	}

	return remark.toStdString();
}

Order CreateOrderDialog::getOrder()
{
	// получаем данные заказа

	Order order;
	QDateTime currentDateTime = QDateTime::currentDateTime();

	if (_idEditOrder == -1)
	{
		order.setId(DataBase::getLastId(DataBase::getTableOrders()) + 1);
		order.setLoginCreate(getLogin().getId());
		order.setLoginEdit(0);
		order.setLoginAvailability(0);
		order.setDateTimeCreate(currentDateTime);
	}
	else
	{
		order.setId(_idEditOrder);
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
	order.setRemark(getRemark());

	int managerId = 0;
	int designerId = 0;
	int clientId = 0;


	if (managersComboBox->currentIndex() != -1)
	{
		managerId = managersComboBox->currentData().toInt();
		order.setManager(DataBase::getStaff(managerId));
	}
	else
	{
		//QMessageBox::information(this, "Title", "не выбран менеджер");
		order.setManager(Staff(0));
	}

	if (designersComboBox->currentIndex() != -1) 
	{
		designerId = designersComboBox->currentData().toInt();
		order.setDesigner(DataBase::getStaff(designerId));
	}
	else
	{
		//QMessageBox::information(this, "Title", "не выбран дизайнер");
		order.setDesigner(Staff(0));
	}

	if (clientsComboBox->currentIndex() != -1) 
	{
		clientId = clientsComboBox->currentData().toInt();
		order.setClient(DataBase::getClient(clientId));
	}
	else
	{
		//QMessageBox::information(this, "Title", "не выбран клиент");
		order.setClient(Client(0, "", "", ""));
	}

	order.setPositionsList(getPositionsList());

	return order;
}

void CreateOrderDialog::openCalendarSlot()
{
	//открыть календарь для установки даты

	SetDateDialog setDateDialog(this);
	setDateDialog.calendarWidget->setSelectedDate(dateEdit->date());
	QPoint point = QCursor::pos();
	point.setX(point.x() - setDateDialog.width() / 2);
	point.setY(point.y() - setDateDialog.height() / 2);
	setDateDialog.move(point);
	setDateDialog.setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	if (setDateDialog.exec())
	{
		dateEdit->setDate(setDateDialog.calendarWidget->selectedDate());
	}
}

void CreateOrderDialog::addOrderToDBSlot()
{
	//внести заказ в БД

	DataBase::addOrder(getOrder());
	accept();
}

void CreateOrderDialog::addPositionSlot()
{
	//добавить позицию

	addPosition();
	descriptionTextEdit->clear();
	quantityLineEdit->clear();
	issueComboBox->setCurrentIndex(-1);
}

void CreateOrderDialog::removePositionSlot()
{
	//удаляем позицию заказа

	int currRow = positionTableWidget->currentRow();
	positionTableWidget->removeRow(currRow);
}

void CreateOrderDialog::saveChangesSlot()
{
	//сохраняем изменения

	DataBase::editOrder(getOrder());
	accept();
}


	

