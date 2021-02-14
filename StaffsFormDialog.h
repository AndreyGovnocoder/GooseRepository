#pragma once

#include <QDialog>
#include "ui_StaffsFormDialog.h"
#include "MainForm.h"
#include "Staff.h"
#include "DataBase.h"
#include "AddStaffDialog.h"
#include "EditStaffDialog.h"

class StaffsFormDialog : public QDialog, public Ui::StaffsFormDialog
{
	Q_OBJECT

public:
	StaffsFormDialog(QWidget* parent = Q_NULLPTR);
	~StaffsFormDialog() = default;
	void setStaffList();
	void setSelectedStaffId(int selectedStaffId) { _staffId = selectedStaffId; };
	const int getSelectedStaffId() const { return _staffId; };

private:
	int _staffId;

private slots:
	void addManagerSlot();
	void editStaffSlot();
	void removeStaffSlot();
	void addDesignerSlot();
	void clickOnManagerSlot();
	void clickOnDesignerSlot();
};
