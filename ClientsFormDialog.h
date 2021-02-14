#pragma once

#include <QDialog>
#include "ui_ClientsFormDialog.h"
#include "Client.h"
#include "DataBase.h"
#include "MainForm.h"
#include "EditClientDialog.h"
#include "AddClientDialog.h"

class ClientsFormDialog : public QDialog, public Ui::ClientsFormDialog
{
	Q_OBJECT

public:
	ClientsFormDialog(QWidget *parent = Q_NULLPTR);
	~ClientsFormDialog() = default;
	void setClients(const std::vector<Client>& clientsList);

private:
	const int getCurrentId();

private slots:
	void removeClientSlot();
	void editClientSlot();
	void addClientSlot();
};
