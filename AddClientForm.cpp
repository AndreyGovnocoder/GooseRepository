#include "AddClientForm.h"
#include "Client.h"
#include "DataBase.h"

AddClientForm::AddClientForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

void AddClientForm::addClientToDBSlot() 
{
	//получаем из формы данные клиента

	Client client(nameLineEdit->text().toStdString(), phoneLineEdit->text().toStdString(), mailLineEdit->text().toStdString());
	DataBase::addClient(client);
	close();
}
