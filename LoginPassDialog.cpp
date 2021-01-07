#include "LoginPassDialog.h"


LoginPassDialog::LoginPassDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

void LoginPassDialog::createAccountSlot() 
{
	//создание учетной записи
	
	CreateAccountForm *createAcc = new CreateAccountForm;
	createAcc->setWindowTitle("Создание учетной записи");
	createAcc->setWindowModality(Qt::WindowModality::ApplicationModal);
	createAcc->setAttribute(Qt::WA_DeleteOnClose);
	createAcc->show();
}

void LoginPassDialog::checkLoginPassSlot() 
{
	// сверяем логин и пароль

	std::vector<StaffAccount> accountsList(DataBase::getAccountsList());
	StaffAccount account;
	account.setLogin(loginLineEdit->text().toStdString());
	account.setPassword(passwordLineEdit->text().toStdString());

	for (int i = 0; i < accountsList.size(); ++i)
	{
		if (account.getLogin() == accountsList[i].getLogin())
		{
			if (account.getPassword() == accountsList[i].getPassword())
			{
				account.setId(accountsList[i].getId());
				account.setName(accountsList[i].getName());
				account.setPosition(accountsList[i].getPosition());
				setAccount(account);
				accept();
				break;
			}
			else 
			{
				//QMessageBox::warning(this, "Ошибка", "Неверный пароль");
				break;
			}
		}

		if (i == (accountsList.size() - 1))
		{
			//QMessageBox::warning(this, "Ошибка", "Неверный логин");
		}
	}
}



