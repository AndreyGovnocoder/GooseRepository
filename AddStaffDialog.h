#pragma once

#include <QDialog>
#include "ui_AddStaffDialog.h"

class AddStaffDialog : public QDialog, public Ui::AddStaffDialog
{
	Q_OBJECT

public:
	AddStaffDialog(QWidget* parent = Q_NULLPTR);
	~AddStaffDialog() = default;
};
