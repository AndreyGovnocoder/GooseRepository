#pragma once

#include <QDialog>
#include "ui_LoginPassDialog.h"
#include "StaffAccount.h"
#include "CreateAccountForm.h"
#include "StaffAccount.h"
#include "DataBase.h"
#include "MainForm.h"
#include <QtWidgets\qmessagebox.h>

class LoginPassDialog : public QDialog, public Ui::LoginPassDialog
{
	Q_OBJECT

public:
	LoginPassDialog(QWidget *parent = Q_NULLPTR);
	~LoginPassDialog() = default;
	void setAccountId(int accountId) { _accountId = accountId; }
	int getAccountId() { return _accountId; };

private:
	int _accountId;

private slots:
	void createAccountSlot();
	void checkLoginPassSlot();
};
