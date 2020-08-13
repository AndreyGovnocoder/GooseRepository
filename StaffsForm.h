#pragma once

#include <QWidget>
#include "ui_StaffsForm.h"

class StaffsForm : public QWidget, public Ui::StaffsForm
{
	Q_OBJECT

public:
	StaffsForm(QWidget *parent = Q_NULLPTR);
	~StaffsForm();
	void setStaffList();
	void setSelectedStaffId(int);
	int getSelectedStaffId();

private slots:
	void slot1();
	void slot2();
	void slot3();
	void slot4();
	void slot5();
	void slot6();

private:
	int staffId;
};
