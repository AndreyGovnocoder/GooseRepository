#pragma once

#include <QDialog>
#include "ui_EditClientDialog.h"

class EditClientDialog : public QDialog, public Ui::EditClientDialog
{
	Q_OBJECT

public:
	EditClientDialog(QWidget* parent = Q_NULLPTR) { setupUi(this); };
	~EditClientDialog() = default;
};
