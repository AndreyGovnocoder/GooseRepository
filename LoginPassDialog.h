#pragma once

#include <QDialog>
#include "ui_LoginPassDialog.h"
#include "StaffAccount.h"
#include "CreateAccountForm.h"
#include "StaffAccount.h"
#include "DataBase.h"
#include <QtWidgets\qmessagebox.h>

class LoginPassDialog : public QDialog, public Ui::LoginPassDialog
{
	Q_OBJECT

private:
	StaffAccount _account;

private slots:
	void createAccountSlot();
	void checkLoginPassSlot();

public:
	LoginPassDialog(QWidget *parent = Q_NULLPTR);
	~LoginPassDialog() = default;
	void setAccount(const StaffAccount& account) { _account = account; }
	const StaffAccount& getAccount() const { return _account; };

};
