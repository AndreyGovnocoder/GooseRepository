#pragma once

#include <QWidget>
#include "ui_CreateLoginForm.h"

class CreateLoginForm : public QWidget, public Ui::CreateLoginForm
{
	Q_OBJECT

private slots:
	void addLoginToDBSlot();

public:
	CreateLoginForm(QWidget *parent = Q_NULLPTR);
	~CreateLoginForm() = default;
};
