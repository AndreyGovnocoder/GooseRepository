#pragma once

#include <QDialog>
#include "ui_AddClientDialog.h"
#include "Client.h"
#include "DataBase.h"
#include "MainForm.h"

class AddClientDialog : public QDialog, public Ui::AddClientDialog
{
	Q_OBJECT

public:
	AddClientDialog(QWidget *parent = Q_NULLPTR);
	~AddClientDialog() = default;

private slots:
	void addClientToDBSlot();
};
