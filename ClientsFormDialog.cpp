#include "ClientsFormDialog.h"

ClientsFormDialog::ClientsFormDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
    setClients(MainForm::_clientsList);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

void ClientsFormDialog::setClients(const std::vector<Client>& clientsList)
{
    // заполняем таблицу данными

    clientsTableWidget->clearContents();
    clientsTableWidget->setRowCount(0);

    if (!clientsList.empty())
    {
        for (size_t i = 0; i < clientsList.size(); ++i)
        {
            if (clientsList[i].isActive())
            {
                clientsTableWidget->insertRow(i);
                clientsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(clientsList[i].getId()))));
                clientsTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(clientsList[i].getName())));
                clientsTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(clientsList[i].getPhone())));
                clientsTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(clientsList[i].getMail())));
            }            
        }

        clientsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        clientsTableWidget->resizeColumnsToContents();
        clientsTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        clientsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        clientsTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        clientsTableWidget->setColumnHidden(0, true);
        clientsTableWidget->horizontalHeader()->setStretchLastSection(true);
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

const int ClientsFormDialog::getCurrentId()
{
    //получаем id выделенного в списке клиента

    int row;
    int id = -1;

    if (clientsTableWidget->currentItem())
    {
        row = clientsTableWidget->currentItem()->row();
        id = clientsTableWidget->item(row, 0)->text().toInt();
    }

    return id;
}

void ClientsFormDialog::removeClientSlot()
{
    // удаление данных клиента

    if (getCurrentId() != -1)
    {
        int removeClientId = getCurrentId();
        if (MainForm::checkClientInOrders(removeClientId))
        {
            if (Client* editClient = MainForm::findClient(removeClientId))
            {
                editClient->setActive(false);
                if (DataBase::editClient(editClient))
                    setClients(MainForm::_clientsList);                
                else
                    QMessageBox::critical(this, "Ошибка", "Ошибка при удалении клиента");
            }
        }
        else
        {
            if (DataBase::removeClient(removeClientId))
            {
                auto it = std::remove_if(MainForm::_clientsList.begin(), MainForm::_clientsList.end(), [&removeClientId](const Client& client) {return client.getId() == removeClientId; });
                MainForm::_clientsList.erase(it, MainForm::_clientsList.end());
                setClients(MainForm::_clientsList);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Ошибка при удалении клиента");
        }
    }
}

void ClientsFormDialog::editClientSlot()
{
    // редактирование данных клиента

    if (getCurrentId() != -1)
    {
        int currId = getCurrentId();
        std::string name;
        std::string phone;
        std::string mail;

        EditClientDialog editDialog(this);
        editDialog.setWindowTitle("Редактирование данных клиента");
        if (const Client* client = MainForm::findClient(currId))
        {
            editDialog.nameLineEdit->setText(QString::fromStdString(client->getName()));
            editDialog.phoneLineEdit->setText(QString::fromStdString(client->getPhone()));
            editDialog.mailLineEdit->setText(QString::fromStdString(client->getMail()));

            if (editDialog.exec())
            {
                name = editDialog.nameLineEdit->text().toStdString();
                phone = editDialog.phoneLineEdit->text().toStdString();
                mail = editDialog.mailLineEdit->text().toStdString();
                const Client editClient(currId, name, phone, mail, true);
                if (DataBase::editClient(editClient))
                {
                    std::replace_if(MainForm::_clientsList.begin(), MainForm::_clientsList.end(), [&editClient](const Client& client) {return editClient.getId() == client.getId(); }, editClient);
                    setClients(MainForm::_clientsList);
                }

                else
                    QMessageBox::warning(this, "", "Ошибка сохранения изменений");
            }
        }
    }
}

void ClientsFormDialog::addClientSlot()
{
    AddClientDialog addClientDialog;
    addClientDialog.setWindowTitle("Новый клиент");
    addClientDialog.setWindowModality(Qt::WindowModality::ApplicationModal);
    if (addClientDialog.exec())
        setClients(MainForm::_clientsList);
}