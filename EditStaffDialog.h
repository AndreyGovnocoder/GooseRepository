#pragma once

#include <QDialog>
#include "ui_EditStaffDialog.h"

class EditStaffDialog : public QDialog, public Ui::EditStaffDialog
{
	Q_OBJECT

public:
	EditStaffDialog(QWidget* parent = Q_NULLPTR) { setupUi(this); };
	~EditStaffDialog() = default;
};
