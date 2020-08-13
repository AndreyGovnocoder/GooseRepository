#pragma once

#include <QWidget>
#include "ui_ClientsForm.h"
#include "Client.h"

class ClientsForm : public QWidget, public Ui::ClientsForm
{
	Q_OBJECT

public:
	ClientsForm(QWidget *parent = Q_NULLPTR);
	~ClientsForm();
	void setClients(std::vector<Client>);

private slots:
	void slot1();
	void slot2();

private:
	int getCurrentId();
};
