#include "CreateAccountForm.h"

CreateAccountForm::CreateAccountForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

void CreateAccountForm::addAccountToDBSlot()
{
	//сохраняем логин в БД
	StaffAccount account;

	account.setName(nameLineEdit->text().toStdString());
	account.setPosition(positionLineEdit->text().toStdString());
	account.setLogin(loginLineEdit->text().toStdString());
	account.setPassword(passwordLineEdit->text().toStdString());
	const std::vector<StaffAccount>& accountsList = DataBase::getAccountsList();

	std::string accountLogin = account.getLogin();
	
	if (std::find_if(accountsList.begin(), accountsList.end(), [&accountLogin](const StaffAccount& account) {return account.getLogin() == accountLogin; }) != accountsList.end())
		QMessageBox::warning(this, "Ошибка", "Такой логин уже существует");
	else
	{
		//добавляем в бд
		if(DataBase::addAccount(account))
		{
			QMessageBox::information(this, "", "Аккаунт успешно добавлен");
			close();
		}
		else
			QMessageBox::critical(this, "Ошибка", "Ошибка при добавлении аккаунта в базу данных");
	}
}