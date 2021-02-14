#pragma once

#include <QDialog>
#include "ui_PrintReceiptDialog.h"
#include "Order.h"
#include "Client.h"
#include "Staff.h"
#include <qmessagebox.h>
#include "MainForm.h"
#include <QStandardItemModel>
#include "ToPrintForm.h"
#include <QtPrintSupport/qprinter.h>
#include <QPrintDialog>
#include <QtGui>
#include <QtCore>


class PrintReceiptDialog : public QDialog, public Ui::PrintReceiptDialog
{
	Q_OBJECT

public:
	PrintReceiptDialog(const Order* order, QWidget *parent = Q_NULLPTR);
	~PrintReceiptDialog() = default;

private:
	const Order* _order;
	std::vector<OrderPosition*> _positionsToPrint;
	QStandardItemModel* _model;
	void setOrderDataToUi();
	void setPositionsTableWidget();
	void setPositionsToPrintTableView();

private slots:
	void positionSelectSlot();
	void printReceiptSlot();
};
