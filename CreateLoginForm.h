#pragma once

#include <QWidget>
#include "ui_CreateLoginForm.h"

class CreateLoginForm : public QWidget, public Ui::CreateLoginForm
{
	Q_OBJECT

public:
	CreateLoginForm(QWidget *parent = Q_NULLPTR);
	~CreateLoginForm();

private slots:
	void slot1();
};
