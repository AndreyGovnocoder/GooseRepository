#include "CreateLoginForm.h"
#include "DataBase.h"
#include "StaffLogin.h"
#include <qmessagebox.h>

CreateLoginForm::CreateLoginForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

CreateLoginForm::~CreateLoginForm(){}

void CreateLoginForm::slot1() {
	//сохраняем логин в БД

	StaffLogin* login = new StaffLogin();

	int newId;
	newId = DataBase::getLastId(DataBase::getTableLogins());
	newId++;

	login->setId(newId);
	login->setName(nameLineEdit->text().toStdString());
	login->setPosition(positionLineEdit->text().toStdString());
	login->setLogin(loginLineEdit->text().toStdString());
	login->setPassword(passwordLineEdit->text().toStdString());
	
	std::vector<StaffLogin>* loginsList = new std::vector<StaffLogin>(DataBase::getLoginsList());

	if (!loginsList->empty()) {
		for (int i = 0; i < loginsList->size(); i++) {
			if (login->getLogin() == (*loginsList)[i].getLogin()) {
				QMessageBox::warning(this, "Ошибка", "Такой логин уже существует");
				break;
			}

			if (i == (loginsList->size() - 1)) {
				DataBase::addLogin(login);
				QWidget::close();
				delete loginsList;
			}
		}
	}
	else {
		DataBase::addLogin(login);
		QWidget::close();
		delete loginsList;
	}	
}