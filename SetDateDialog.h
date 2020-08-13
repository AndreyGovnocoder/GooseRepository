#pragma once

#include <QDialog>
#include "ui_SetDateDialog.h"

class SetDateDialog : public QDialog, public Ui::SetDateDialog
{
	Q_OBJECT

public:
	SetDateDialog(QDate, QWidget* parent = Q_NULLPTR);
	~SetDateDialog();
};
