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

void LoginPassDialog::createLoginSlot() 
{
	//создание учетной записи
	
	CreateLoginForm *create = new CreateLoginForm;
	create->setWindowTitle("Создание учетной записи");
	create->setWindowModality(Qt::WindowModality::ApplicationModal);
	create->setAttribute(Qt::WA_DeleteOnClose);
	create->show();
}

void LoginPassDialog::checkLoginPassSlot() 
{
	// сверяем логин и пароль

	std::vector<StaffLogin> loginsList(DataBase::getLoginsList());
	StaffLogin login;
	login.setLogin(loginLineEdit->text().toStdString());
	login.setPassword(passwordLineEdit->text().toStdString());

	for (int i = 0; i < loginsList.size(); ++i) 
	{
		if (login.getLogin() == loginsList[i].getLogin()) 
		{
			if (login.getPassword() == loginsList[i].getPassword()) 
			{
				login.setId(loginsList[i].getId());
				login.setName(loginsList[i].getName());
				login.setPosition(loginsList[i].getPosition());
				setLogin(login);
				accept();
				break;
			}
			else 
			{
				//QMessageBox::warning(this, "Ошибка", "Неверный пароль");
				break;
			}
		}

		if (i == (loginsList.size() - 1)) 
		{
			//QMessageBox::warning(this, "Ошибка", "Неверный логин");
		}
	}
}

void LoginPassDialog::setLogin(const StaffLogin& login) 
{
	_login = login;	
}

