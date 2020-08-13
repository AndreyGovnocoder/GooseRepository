#pragma once

#include <QDialog>
#include "ui_AddStaffForm.h"

class AddStaffForm : public QDialog, public Ui::AddStaffForm
{
	Q_OBJECT

public:
	AddStaffForm(QWidget *parent = Q_NULLPTR);
	AddStaffForm(std::string, QWidget* parent = Q_NULLPTR);
	~AddStaffForm();
	void setPosition(std::string);
	std::string getPosition();

private:
	std::string position;
};
