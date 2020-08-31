#pragma once

#include <QWidget>
#include "ui_ClientsForm.h"
#include "Client.h"

class ClientsForm : public QWidget, public Ui::ClientsForm
{
	Q_OBJECT

private:
	const int getCurrentId();

private slots:
	void removeClientSlot();
	void editClientSlot();

public:
	ClientsForm(QWidget *parent = Q_NULLPTR);
	~ClientsForm() = default;
	void setClients(const std::vector<Client>&);

};
