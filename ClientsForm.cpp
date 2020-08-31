#include "ClientsForm.h"
#include "Client.h"
#include "DataBase.h"
#include "EditClientDialog.h"

ClientsForm::ClientsForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	setClients(DataBase::getClientsList());
}

void ClientsForm::removeClientSlot() 
{
    // удаление данных клиента

    if(getCurrentId() != -1)
    {
        DataBase::removeClient(getCurrentId());
        setClients(DataBase::getClientsList());
    }        
}

void ClientsForm::editClientSlot() 
{
    // редактирование данных клиента

    if (getCurrentId() != -1)
    {
        int currId = getCurrentId();
        std::string name;
        std::string phone;
        std::string mail;

        EditClientDialog editDialog(this);
        Client client(DataBase::getClient(currId));
        editDialog.nameLineEdit->setText(QString::fromStdString(client.getName()));
        editDialog.phoneLineEdit->setText(QString::fromStdString(client.getPhone()));
        editDialog.mailLineEdit->setText(QString::fromStdString(client.getMail()));

        if (editDialog.exec())
        {
            name = editDialog.nameLineEdit->text().toStdString();
            phone = editDialog.phoneLineEdit->text().toStdString();
            mail = editDialog.mailLineEdit->text().toStdString();

            DataBase::editClient(Client(currId, name, phone, mail));

            setClients(DataBase::getClientsList());
        }
    }    
}

void ClientsForm::setClients(const std::vector<Client>& clientsList) 
{
    // заполняем таблицу данными

    clientsTableWidget->clearContents();
    clientsTableWidget->setRowCount(0);

    if (!clientsList.empty())
    {
        for (int i = 0; i < clientsList.size(); ++i)
        {
            clientsTableWidget->insertRow(i);
            clientsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(clientsList[i].getId()))));
            clientsTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(clientsList[i].getName())));
            clientsTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(clientsList[i].getPhone())));
            clientsTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(clientsList[i].getMail())));
        }

        clientsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        clientsTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        clientsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        clientsTableWidget->resizeColumnsToContents();
        clientsTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        clientsTableWidget->setColumnHidden(0, true);
        clientsTableWidget->horizontalHeader()->setStretchLastSection(false);
        clientsTableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        clientsTableWidget->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
    }
    else 
    {
        for (int i = 0; i <= 3; ++i)
        {
            clientsTableWidget->hideColumn(i);
        }

        clientsTableWidget->insertRow(0);
        clientsTableWidget->insertColumn(0);
        clientsTableWidget->setItem(0, 0, new QTableWidgetItem("Список клиентов пуст"));
        clientsTableWidget->horizontalHeader()->setStretchLastSection(false);
    }
}

int ClientsForm::getCurrentId() 
{
    //получаем id выделенного в списке клиента

    int row;
    int id = -1;

    if (clientsTableWidget->currentItem() != NULL)
    {
        row = clientsTableWidget->currentItem()->row();
        id = clientsTableWidget->item(row, 0)->text().toInt();
    }

    return id;
}
