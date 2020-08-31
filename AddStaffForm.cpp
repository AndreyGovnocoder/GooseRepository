#include "AddStaffForm.h"

AddStaffForm::AddStaffForm(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

AddStaffForm::AddStaffForm(const std::string& position, QWidget* parent)
	: QDialog(parent)
{
	setPosition(position);
	setupUi(this);
}