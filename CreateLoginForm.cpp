#include "CreateLoginForm.h"
#include "DataBase.h"
#include "StaffLogin.h"
#include <qmessagebox.h>

CreateLoginForm::CreateLoginForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

void CreateLoginForm::addLoginToDBSlot() 
{
	//сохраняем логин в БД
	StaffLogin login;

	login.setName(nameLineEdit->text().toStdString());
	login.setPosition(positionLineEdit->text().toStdString());
	login.setLogin(loginLineEdit->text().toStdString());
	login.setPassword(passwordLineEdit->text().toStdString());
	
	std::vector<StaffLogin> loginsList(DataBase::getLoginsList());

	for (int i = 0; i < loginsList.size(); ++i)
	{
		if (login.getLogin() == loginsList[i].getLogin())
		{
			QMessageBox::warning(this, "Ошибка", "Такой логин уже существует");
			break;
		}

		if (i == (loginsList.size() - 1))
		{
			DataBase::addLogin(login);
			close();
		}
	}
}