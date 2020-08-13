#pragma once

#include <QDialog>
#include "ui_EditClientDialog.h"

class EditClientDialog : public QDialog, public Ui::EditClientDialog
{
	Q_OBJECT

public:
	EditClientDialog(QWidget *parent = Q_NULLPTR);
	EditClientDialog(int, QWidget* parent = Q_NULLPTR);
	~EditClientDialog();
	int getClientId();
	
private:
	int id;
	void setClient(QString, QString, QString);
};
