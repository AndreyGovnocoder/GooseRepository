#include "EditClientDialog.h"
#include "DataBase.h"

EditClientDialog::EditClientDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

EditClientDialog::EditClientDialog(int idClient, QWidget* parent)
	: QDialog(parent)
{
	id = idClient;

	for (int i = 0; i < DataBase::getClientsList().size(); i++) {
		if (DataBase::getClientsList()[i].getId() == id) {
			QString name = QString::fromStdString(DataBase::getClientsList()[i].getName());
			QString phone = QString::fromStdString(DataBase::getClientsList()[i].getPhone());
			QString mail = QString::fromStdString(DataBase::getClientsList()[i].getMail());

			EditClientDialog::setClient(name, phone, mail);
		}
	}
}

EditClientDialog::~EditClientDialog(){}

void EditClientDialog::setClient(QString name, QString phone, QString mail) {
	nameLineEdit->setText(name);
	phoneLineEdit->setText(phone);
	mailLineEdit->setText(mail);
}

int EditClientDialog::getClientId() {
	return id;
}
