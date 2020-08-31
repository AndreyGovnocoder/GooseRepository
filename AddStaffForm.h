#pragma once

#include <QDialog>
#include "ui_AddStaffForm.h"

class AddStaffForm : public QDialog, public Ui::AddStaffForm
{
	Q_OBJECT

private:
	std::string _position;

public:
	AddStaffForm(QWidget *parent = Q_NULLPTR);
	AddStaffForm(const std::string&, QWidget* parent = Q_NULLPTR);
	~AddStaffForm() = default;
	void setPosition(const std::string& position) { _position = position; };
	const std::string& getPosition() const { return _position; };

};
