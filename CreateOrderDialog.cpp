#include "CreateOrderDialog.h"

CreateOrderDialog::CreateOrderDialog(QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);
	setCurrentDate();
	setClientsList();
	setPayment();
	setManagersList();
	setDesignersList();
	setIssueComboBox();
	saveBtn->setVisible(false);
}

CreateOrderDialog::CreateOrderDialog(QWidget* parent, Order* editOrder)
	: QDialog(parent)
{
	_editOrder = editOrder;
	setupUi(this);
	setClientsList();
	setPayment();
	setManagersList();
	setDesignersList();
	setIssueComboBox();
	setEditOrderToUI();
	addOrderBtn->setVisible(false);
}

void CreateOrderDialog::setPositionsList(const std::vector<OrderPosition>& positionsList)
{
	//добавляем в таблицу список позиций заказа

	int row = 0;

	for (const auto& position : positionsList)
	{
		QString description;
		QString descr;
		QStringList descriptionList;
		description = QString::fromStdString(position.getDescription());
		descriptionList = description.split('^');

		for (size_t i = 0; i < descriptionList.size(); ++i)
		{
			descr.append(descriptionList.at(i));
			if (i != (descriptionList.size() - 1)) 
				descr.append('\n');
		}

		QString quantity = QString::fromStdString(position.getQuantity());
		QString issue = QString::fromStdString(position.getIssue());

		positionTableWidget->insertRow(row);
		positionTableWidget->setItem(row, 0, new QTableWidgetItem(descr));
		positionTableWidget->setItem(row, 1, new QTableWidgetItem(quantity));
		positionTableWidget->setItem(row, 2, new QTableWidgetItem(issue));

		++row;
	}

	positionTableWidget->resizeColumnsToContents();
	positionTableWidget->resizeRowsToContents();
	positionTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	positionTableWidget->horizontalHeaderItem(2)->setTextAlignment(50);
}

void CreateOrderDialog::setCurrentDate()
{
	dateEdit->setDate(QDate::currentDate());
}

void CreateOrderDialog::setClientsList()
{
	//устанавливаем список клиентов в comboBox
	int index = 0;

	for (const auto& client : MainForm::_clientsList)
	{
		if (client.isActive())
		{
			QVariant var;
			var.setValue(client.getId());
			clientsComboBox->addItem(QString::fromStdString(client.getName()));
			clientsComboBox->setItemData(index, var);
			++index;
		}
	}

	clientsComboBox->setCurrentIndex(-1);
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

	int index = 0;

	for (const auto& staff : MainForm::_staffsList)
	{
		if (staff.isActive() && staff.getPosition() == "менеджер")
		{
			QVariant var;
			var.setValue(staff.getId());
			managersComboBox->addItem(QString::fromStdString(staff.getName()));
			managersComboBox->setItemData(index, var);
			++index;
		}
	}

	managersComboBox->setCurrentIndex(-1);
}

void CreateOrderDialog::setDesignersList()
{
	//устанавливаем список дизайнеров

	int index = 0;

	for (auto& staff : MainForm::_staffsList)
	{
		if (staff.isActive() && staff.getPosition() == "дизайнер")
		{
			QVariant var;
			var.setValue(staff.getId());
			designersComboBox->addItem(QString::fromStdString(staff.getName()));
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

	const int rowCount = positionTableWidget->rowCount();
	QString description = "Описание позиции отсутствует";
	QString quantity = "Не указано";
	QString issue = "Не указано";

	if(!descriptionTextEdit->toPlainText().isEmpty())
		description = descriptionTextEdit->toPlainText();
	if(!quantityLineEdit->text().isEmpty())
		quantity = quantityLineEdit->text();
	if(!issueComboBox->currentText().isEmpty())
		issue = issueComboBox->currentText();

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

std::vector<OrderPosition> CreateOrderDialog::getPositionsList()
{
	//получаем список позиций заказа

	std::vector<OrderPosition> positionsList;

	for (int i = 0; i < positionTableWidget->rowCount(); ++i)
	{
		OrderPosition position;
		std::string quantity = positionTableWidget->item(i, 1)->text().toStdString();
		std::string issue = positionTableWidget->item(i, 2)->text().toStdString();

		if (_editOrder)
			position.setIdOrder(_editOrder->getId());		

		position.setQuantity(quantity);
		position.setIssue(issue);

		QString description = positionTableWidget->item(i, 0)->text();
		QStringList descList = description.split('\n');
		std::string descrString;
		
		for (size_t k = 0; k < descList.size(); ++k)
		{
			descrString.append(descList.at(k).toStdString());
			if (k != (descList.size() - 1)) 
				descrString.append("^");
		}

		position.setDescription(descrString);
		positionsList.push_back(position);
	}

	return positionsList;
}

std::string CreateOrderDialog::getRemark()
{
	// получаем примечание

	const QString remarkString = remarkTextEdit->toPlainText();
	const QStringList remarkList = remarkString.split('\n');
	QString remark;

	for (size_t i = 0; i < remarkList.size(); ++i)
	{
		remark.append(remarkList.at(i));
		if (i != (remarkList.size() - 1)) 
			remark.append("^");
	}

	return remark.toStdString();
}

void CreateOrderDialog::setEditOrder()
{
	// устанавливаем данные заказа в Order
	int managerId = -1;
	int designerId = -1;
	int clientId = -1;
	
	_editOrder->setDateTimeEdit(QDateTime::currentDateTime());
	_editOrder->setAccountEdit(getAccount()->getId());
	_editOrder->setDate(dateEdit->date());
	_editOrder->setAmount(amountLineEdit->text().toStdString());
	_editOrder->setPayment(paymentComboBox->currentText().toStdString());
	_editOrder->setRemark(getRemark());

	if (managersComboBox->currentIndex() != -1)
	{
		managerId = managersComboBox->currentData().toInt();
		_editOrder->setManager(managerId);
	}
	else
		_editOrder->setManager(0);
	

	if (designersComboBox->currentIndex() != -1)
	{
		designerId = designersComboBox->currentData().toInt();
		_editOrder->setDesigner(designerId);
	}
	else
		_editOrder->setDesigner(0);	

	if (clientsComboBox->currentIndex() != -1)
	{
		clientId = clientsComboBox->currentData().toInt();
		_editOrder->setClient(clientId);
	}
	else
		_editOrder->setClient(-1);	

	_editOrder->setPositionsList(getPositionsList());
}

void CreateOrderDialog::setEditOrderToUI()
{
	dateEdit->setDate(_editOrder->getDate());

	if (_editOrder->getClient())
	{
		for (size_t i = 0; i <= clientsComboBox->count(); ++i)
		{
			if (_editOrder->getClient() == clientsComboBox->itemData(i))
				clientsComboBox->setCurrentIndex(i);			
		}
	}
	else
		clientsComboBox->setCurrentIndex(-1);

	for (size_t i = 0; i <= paymentComboBox->count(); ++i)
	{
		if (QString::fromStdString(_editOrder->getPayment()) == paymentComboBox->itemText(i))
			paymentComboBox->setCurrentIndex(i);
	}

	amountLineEdit->setText(QString::fromStdString(_editOrder->getAmount()));

	for (size_t i = 0; i <= managersComboBox->count(); ++i)
	{
		if (_editOrder->getManager() == managersComboBox->itemData(i))
			managersComboBox->setCurrentIndex(i);
	}

	for (size_t i = 0; i <= designersComboBox->count(); ++i)
	{
		if (_editOrder->getDesigner() == designersComboBox->itemData(i))
			designersComboBox->setCurrentIndex(i);
	}

	const QString remarkString = QString::fromStdString(_editOrder->getRemark());
	const QStringList remarkList = remarkString.split('^');
	QString remark;

	for (size_t i = 0; i < remarkList.size(); ++i)
	{
		remark.append(remarkList.at(i));
		if (i != (remarkList.size() - 1)) 
			remark.append("\n");
	}

	remarkTextEdit->setText(remark);
	setPositionsList(_editOrder->getPositionsList());
}

void CreateOrderDialog::setNewOrder()
{
	int managerId = -1;
	int designerId = -1;
	int clientId = -1;

	_newOrder.setAccountCreate(getAccount()->getId());
	_newOrder.setAccountEdit(-1);
	_newOrder.setAccountAvailability(-1);
	_newOrder.setDateTimeCreate(QDateTime::currentDateTime());
	_newOrder.setAvailability("В работе");
	_newOrder.setDate(dateEdit->date());
	_newOrder.setAmount(amountLineEdit->text().toStdString());
	_newOrder.setPayment(paymentComboBox->currentText().toStdString());
	_newOrder.setRemark(getRemark());

	if (managersComboBox->currentIndex() != -1)
	{
		managerId = managersComboBox->currentData().toInt();
		_newOrder.setManager(managerId);
	}
	else
		_newOrder.setManager(-1);

	if (designersComboBox->currentIndex() != -1)
	{
		designerId = designersComboBox->currentData().toInt();
		_newOrder.setDesigner(designerId);
	}
	else
		_newOrder.setDesigner(-1);

	if (clientsComboBox->currentIndex() != -1)
	{
		clientId = clientsComboBox->currentData().toInt();
		_newOrder.setClient(clientId);
	}
	else
		_newOrder.setClient(-1);

	_newOrder.setPositionsList(getPositionsList());
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
		dateEdit->setDate(setDateDialog.calendarWidget->selectedDate());	
}

void CreateOrderDialog::addOrderToDBSlot()
{
	//внести заказ в БД
	setNewOrder();
	_isOk = true;
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

	const int currRow = positionTableWidget->currentRow();
	positionTableWidget->removeRow(currRow);
}

void CreateOrderDialog::saveChangesSlot()
{
	//сохраняем изменения
	setEditOrder();
	_isOk = true;
	accept();
}