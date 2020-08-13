#pragma once

#include <QDialog>
#include "ui_LoginPassDialog.h"
#include "StaffLogin.h"

class LoginPassDialog : public QDialog, public Ui::LoginPassDialog
{
	Q_OBJECT

public:
	LoginPassDialog(QWidget *parent = Q_NULLPTR);
	~LoginPassDialog();
	void setLogin(StaffLogin);
	StaffLogin getLogin();

private slots:
	void slot1();
	void slot2();

private:
	StaffLogin login;
};
