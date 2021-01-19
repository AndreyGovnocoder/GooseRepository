#include "LoginPassDialog.h"


LoginPassDialog::LoginPassDialog(QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);
}

void LoginPassDialog::createAccountSlot()
{
	//создание учетной записи

	CreateAccountForm* createAcc = new CreateAccountForm;
	createAcc->setWindowTitle("Создание учетной записи");
	createAcc->setWindowModality(Qt::WindowModality::ApplicationModal);
	createAcc->setAttribute(Qt::WA_DeleteOnClose);
	createAcc->show();
}

void LoginPassDialog::checkLoginPassSlot()
{
	// сверяем логин и пароль

	std::vector<StaffAccount>& accountsList = DataBase::getAccountsList();
	std::string login = loginLineEdit->text().toStdString();
	std::string password = passwordLineEdit->text().toStdString();
	auto it = std::find_if(accountsList.begin(), accountsList.end(), [&login](const StaffAccount& account) {return account.getLogin() == login; });
	if (it != accountsList.end())
	{
		StaffAccount* account = &(*it);
		if (password == account->getPassword())
		{
			setAccountId(account->getId());
			accept();
		}
		else
			QMessageBox::critical(this, "Ошибка", "Неверный пароль");
	}
	else
		QMessageBox::critical(this, "Ошибка", "Неверный логин");
}