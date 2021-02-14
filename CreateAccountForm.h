#pragma once

#include <QWidget>
#include "ui_CreateAccountForm.h"
#include "DataBase.h"
#include "StaffAccount.h"
#include <qmessagebox.h>

class CreateAccountForm : public QWidget, public Ui::CreateAccountForm
{
	Q_OBJECT

public:
	CreateAccountForm(QWidget *parent = Q_NULLPTR);
	~CreateAccountForm() = default;

private slots:
	void addAccountToDBSlot();
};
