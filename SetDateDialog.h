#pragma once

#include <QDialog>
#include "ui_SetDateDialog.h"

class SetDateDialog : public QDialog, public Ui::SetDateDialog
{
	Q_OBJECT

public:
	SetDateDialog(QWidget* parent = Q_NULLPTR) { setupUi(this); };
	~SetDateDialog() = default;
};
