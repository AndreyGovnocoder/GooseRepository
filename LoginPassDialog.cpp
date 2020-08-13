#include "LoginPassDialog.h"
#include "CreateLoginForm.h"
#include "StaffLogin.h"
#include "DataBase.h"
#include <QtWidgets\qmessagebox.h>

LoginPassDialog::LoginPassDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

LoginPassDialog::~LoginPassDialog(){}

void LoginPassDialog::slot1() {
	//создание учетной записи
	
	CreateLoginForm *create = new CreateLoginForm;
	create->setWindowTitle("Создание учетной записи");
	create->setWindowModality(Qt::WindowModality::ApplicationModal);
	create->show();
}

void LoginPassDialog::slot2() {
	// сверяем логин и пароль

	std::vector<StaffLogin>* loginsList = new std::vector<StaffLogin>(DataBase::getLoginsList());
	StaffLogin login;
	login.setLogin(loginLineEdit->text().toStdString());
	login.setPassword(passwordLineEdit->text().toStdString());

	for (int i = 0; i < loginsList->size(); i++) {
		if (login.getLogin() == (*loginsList)[i].getLogin()) {
			if (login.getPassword() == (*loginsList)[i].getPassword()) {
				login.setId((*loginsList)[i].getId());
				login.setName((*loginsList)[i].getName());
				login.setPosition((*loginsList)[i].getPosition());
				setLogin(login);
				QDialog::accept();
				break;
			}
			else {
				QMessageBox::warning(this, "Ошибка", "Неверный пароль");
				break;
			}
		}

		if (i == (loginsList->size() - 1)) {
			QMessageBox::warning(this, "Ошибка", "Неверный логин");
		}
	}
}

void LoginPassDialog::setLogin(StaffLogin login) {
	LoginPassDialog::login.setId(login.getId());
	LoginPassDialog::login.setName(login.getName());
	LoginPassDialog::login.setPosition(login.getPosition());
	LoginPassDialog::login.setLogin(login.getLogin());
	LoginPassDialog::login.setPassword(login.getPassword());
}

StaffLogin LoginPassDialog::getLogin() {
	return LoginPassDialog::login;
}
