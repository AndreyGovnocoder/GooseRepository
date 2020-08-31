#pragma once

#include <QDialog>
#include "ui_LoginPassDialog.h"
#include "StaffLogin.h"

class LoginPassDialog : public QDialog, public Ui::LoginPassDialog
{
	Q_OBJECT

private:
	StaffLogin _login;

private slots:
	void createLoginSlot();
	void checkLoginPassSlot();

public:
	LoginPassDialog(QWidget *parent = Q_NULLPTR);
	~LoginPassDialog() = default;
	void setLogin(const StaffLogin&);
	const StaffLogin& getLogin() const { return _login; };

};
