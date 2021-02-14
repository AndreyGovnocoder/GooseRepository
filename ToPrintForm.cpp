#include "ToPrintForm.h"

ToPrintForm::ToPrintForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	setLogo();
}

void ToPrintForm::setPositionsList(std::vector<OrderPosition*> &positionsToPrint)
{
	QStandardItemModel* model = new QStandardItemModel;
    QStringList horizontalHeader;
    horizontalHeader.append("Наименование работ, услуг");
    horizontalHeader.append("Количество");
    model->setHorizontalHeaderLabels(horizontalHeader);
    
    for (size_t i = 0; i < positionsToPrint.size(); ++i)
    {
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(positionsToPrint[i]->getDescription())));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(positionsToPrint[i]->getQuantity())));
    }
    positionsToPrintTableView->setModel(model);
    positionsToPrintTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    positionsToPrintTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

void ToPrintForm::setupReceiptData()
{
	headLabel->setText("Накладная на отпуск продукции №" + QString::number(_numberReceipt));
	dateLabel->setText("от " + _date);
	clientLabel->setText(_client);
	managerLabel->setText("Менеджер: " + _manager);
}

void ToPrintForm::setLogo()
{
    QPixmap logo("logoPrnt.jpg");
    imageLabel->setPixmap(logo);
}
