#pragma once

#include <QWidget>
#include "ui_AddClientForm.h"

class AddClientForm : public QWidget, public Ui::AddClientForm
{
	Q_OBJECT

private slots:
	void addClientToDBSlot();

public:
	AddClientForm(QWidget *parent = Q_NULLPTR);
	~AddClientForm() = default;

};
