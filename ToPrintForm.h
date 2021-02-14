#pragma once

#include <QWidget>
#include "ui_ToPrintForm.h"
#include "OrderPosition.h"
#include <QStandardItemModel>

class ToPrintForm : public QWidget, public Ui::ToPrintForm
{
	Q_OBJECT

public:
	ToPrintForm(QWidget *parent = Q_NULLPTR);
	~ToPrintForm() = default;
	void setNumberReceipt(const int number) { _numberReceipt = number; }
	void setClient(const QString& client) { _client = client; }
	void setManager(const QString& manager) { _manager = manager; }
	void setDate(const QString& date) { _date = date; }
	void setPositionsList(std::vector<OrderPosition*> &positionsToPrint);
	void setupReceiptData();

private:
	int _numberReceipt;
	QString _client;
	QString _manager;
	QString _date;
	void setLogo();
};
