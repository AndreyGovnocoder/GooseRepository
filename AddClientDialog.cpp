#include "AddClientDialog.h"

AddClientDialog::AddClientDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

void AddClientDialog::addClientToDBSlot()
{
	//получаем из формы данные клиента и добавляем в бд

	Client client(
		nameLineEdit->text().toStdString(), 
		phoneLineEdit->text().toStdString(), 
		mailLineEdit->text().toStdString(), 
		true);
	if (DataBase::addClient(client))
	{
		client.setId(DataBase::getLastId(DataBase::TABLE_CLIENTS));
		MainForm::_clientsList.push_back(std::move(client));
		QMessageBox::information(this, " ", "Клиент успешно добавлен в базу данных");
		accept();
	}
	else
		QMessageBox::warning(this, "", "Ошибка добавления клиента в базу данных");
}
