#pragma once

#include <QWidget>
#include "ui_StaffsForm.h"

class StaffsForm : public QWidget, public Ui::StaffsForm
{
	Q_OBJECT


private:
	int _staffId;

private slots:
	void addManagerSlot();
	void editStaffSlot();
	void removeStaffSlot();
	void addDesignerSlot();
	void clickOnManagerSlot();
	void clickOnDesignerSlot();

public:
	StaffsForm(QWidget *parent = Q_NULLPTR);
	~StaffsForm() = default;
	void setStaffList();
	void setSelectedStaffId(int selectedStaffId) { _staffId = selectedStaffId; };
	int getSelectedStaffId() { return _staffId; };
};
