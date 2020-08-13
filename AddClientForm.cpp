#include "AddClientForm.h"
#include "Client.h"
#include "DataBase.h"

AddClientForm::AddClientForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

AddClientForm::~AddClientForm()
{
}

void AddClientForm::slot1() {
	//получаем из формы данные клиента
	int newId = DataBase::getLastId(DataBase::getTableClients());
	newId++;

	Client* client = new Client(newId, nameLineEdit->text().toStdString(), phoneLineEdit->text().toStdString(), mailLineEdit->text().toStdString());
	DataBase::addClient(client);
	QWidget::close();
}
