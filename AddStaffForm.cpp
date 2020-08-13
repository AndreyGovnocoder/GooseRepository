#include "AddStaffForm.h"

AddStaffForm::AddStaffForm(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

AddStaffForm::AddStaffForm(std::string position, QWidget* parent)
	: QDialog(parent)
{
	AddStaffForm::setPosition(position);
	setupUi(this);
}

AddStaffForm::~AddStaffForm()
{
}

void AddStaffForm::setPosition(std::string position) {
	AddStaffForm::position = position;
}

std::string AddStaffForm::getPosition() {
	return AddStaffForm::position;
}
