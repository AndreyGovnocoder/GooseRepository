#include "PrintReceiptDialog.h"

PrintReceiptDialog::PrintReceiptDialog(const Order* order, QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	_order = order;
    _model = new QStandardItemModel;
	setOrderDataToUi();
    setPositionsTableWidget();    
}

void PrintReceiptDialog::setOrderDataToUi()
{
	dateLabel->setText(_order->getDate().toString("dd.MM.yyyy"));
	if (const Client* client = MainForm::findClient(_order->getClient()))
		clientLabel->setText(QString::fromStdString(client->getName()));
	
	if (const Staff* manager = MainForm::findStaff(_order->getManager()))
		managerLabel->setText(QString::fromStdString(manager->getName()));	
}

void PrintReceiptDialog::setPositionsTableWidget()
{
    std::vector<OrderPosition> positionsList = _order->getPositionsList();
    int positionId;
    QString description;
    QStringList descriptionList;
    QString quantity;
    QString issue;

    positionsTableWidget->clearContents();
    positionsTableWidget->setRowCount(0);
    positionsTableWidget->hideColumn(0);

    
    for (size_t i = 0; i < positionsList.size(); ++i)
    {
        QString descr;
        positionId = positionsList[i].getIdPosition();
        description = QString::fromStdString(positionsList[i].getDescription());
        descriptionList = description.split('^');
        QCheckBox* checkBox;

        for (size_t k = 0; k < descriptionList.size(); ++k)
        {
            descr.append(descriptionList.at(k));
            if (k != (descriptionList.size() - 1)) 
                descr.append('\n');
        }
        quantity = QString::fromStdString(positionsList[i].getQuantity());
        issue = QString::fromStdString(positionsList[i].getIssue());

        QTableWidgetItem* positionIdItem = new QTableWidgetItem(QString::number(positionId));
        positionIdItem->setData(Qt::UserRole, positionId);

        positionsTableWidget->insertRow(i);
        positionsTableWidget->setItem(i, 0, positionIdItem);
        positionsTableWidget->setItem(i, 1, new QTableWidgetItem(descr));
        positionsTableWidget->setItem(i, 2, new QTableWidgetItem(quantity));
        positionsTableWidget->setItem(i, 3, new QTableWidgetItem(issue));
    }

    positionsTableWidget->resizeColumnsToContents();
    positionsTableWidget->resizeRowsToContents();
    positionsTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    positionsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void PrintReceiptDialog::setPositionsToPrintTableView()
{
    _model->clear();
    QStandardItem* item;
    QStringList horizontalHeader;
    horizontalHeader.append("Наименование работ, услуг");
    horizontalHeader.append("Количество");

    _model->setHorizontalHeaderLabels(horizontalHeader);    
    
    for (size_t i = 0; i < _positionsToPrint.size(); ++i)
    {
        item = new QStandardItem(QString::fromStdString(_positionsToPrint[i]->getDescription()));
        _model->setItem(i, 0, item);
        item = new QStandardItem(QString::fromStdString(_positionsToPrint[i]->getQuantity()));
        _model->setItem(i, 1, item);
    }
    positionsToPrintTableView->setModel(_model);
    positionsToPrintTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    positionsToPrintTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

void PrintReceiptDialog::positionSelectSlot()
{
    _positionsToPrint.clear();
    const int rows = positionsTableWidget->rowCount();
    for (int i = 0; i < rows; ++i)
    {
        if (positionsTableWidget->item(i, 0)->isSelected())
        {
            if (OrderPosition* position = MainForm::findPosition(positionsTableWidget->item(i, 0)->data(Qt::UserRole).toInt()))
                _positionsToPrint.push_back(std::move(position));
        }
    }

    setPositionsToPrintTableView();
}

void PrintReceiptDialog::printReceiptSlot()
{
    //ToPrintForm* printForm = new ToPrintForm();
    std::unique_ptr<ToPrintForm> printForm(new ToPrintForm());

    printForm->setNumberReceipt(DataBase::getReceiptCount());
    printForm->setDate(dateLabel->text());
    printForm->setClient(clientLabel->text());
    printForm->setManager(managerLabel->text());
    printForm->setPositionsList(_positionsToPrint);
    printForm->setupReceiptData();
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setPaperSize(QPrinter::A5);
    printer.setFullPage(false);
    printer.setFromTo(0, 1);
    printer.setOrientation(QPrinter::Landscape);

    QPixmap pixmap(1240,874);
    printForm->widget->render(&pixmap);
    pixmap.toImage().save("receipt.png", "PNG");

    //QPrintDialog* dlg = new QPrintDialog(&printer, this);
    std::unique_ptr<QPrintDialog> dlg(new QPrintDialog(&printer, this));

    if (dlg->exec() == QDialog::Accepted) 
    {
        QImage img("receipt.png");
        QPainter painter(&printer);
        painter.drawImage(QPoint(0, 0), img);
        painter.end();
        DataBase::incrementReceiptCount();
        close();
    }

    //delete dlg;
    //delete printForm;
}