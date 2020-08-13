#include "StaffsForm.h"
#include "Staff.h"
#include "DataBase.h"
#include "AddStaffForm.h"
#include "EditStaffDialog.h"

StaffsForm::StaffsForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	StaffsForm::setSelectedStaffId(-1);
	StaffsForm::setStaffList();
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
}

StaffsForm::~StaffsForm(){}

void StaffsForm::slot1() {
	//добавить менеджера

	AddStaffForm* addStaffDialog = new AddStaffForm(this);
	addStaffDialog->setWindowTitle("Менеджер");

	if (addStaffDialog->exec()) {
		Staff* newStaff = new Staff();
		newStaff->setPosition("менеджер");
		newStaff->setName(addStaffDialog->nameLineEdit->text().toStdString());
		int newId = DataBase::getLastId(DataBase::getTableStaff());
		newId++;
		newStaff->setId(newId);
		DataBase::addStaff(newStaff);
		delete newStaff;
		setStaffList();
	}
}

void StaffsForm::slot4() {
	//добавить дизайнера

	AddStaffForm* addStaffDialog = new AddStaffForm(this);
	addStaffDialog->setWindowTitle("Дизайнер");
	if (addStaffDialog->exec()) {
		Staff* newStaff = new Staff();
		newStaff->setPosition("дизайнер");
		newStaff->setName(addStaffDialog->nameLineEdit->text().toStdString());
		int newId = DataBase::getLastId(DataBase::getTableStaff());
		newId++;
		newStaff->setId(newId);
		DataBase::addStaff(newStaff);
		delete newStaff;
		setStaffList();
	}
}

void StaffsForm::setStaffList() {
	//заполняем listWidget'ы сотрудниками

	designersListWidget->clear();
	managersListWidget->clear();
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
	setSelectedStaffId(-1);

	std::vector<Staff>* staffList = new std::vector<Staff>(DataBase::getStaffList());
	for (int i = 0; i < staffList->size(); i++) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString((*staffList)[i].getName()));
		item->setData(Qt::UserRole, (*staffList)[i].getId());
		if ((*staffList)[i].getPosition() == "менеджер") {
			managersListWidget->addItem(item);
		}
		else {
			designersListWidget->addItem(item);
		}
	}
}

void StaffsForm::slot2() {
	//редактировать сотрудника

	if (getSelectedStaffId() != -1) {
		EditStaffDialog editDialog(this);
		editDialog.setWindowTitle("Редактирование сотрудника");
		Staff staff;
		for (int i = 0; i < DataBase::getStaffList().size(); i++) {
			if (DataBase::getStaffList()[i].getId() == getSelectedStaffId()) {
				staff.setName(DataBase::getStaffList()[i].getName());
				staff.setPosition(DataBase::getStaffList()[i].getPosition());
				staff.setId(DataBase::getStaffList()[i].getId());
			}
		}
		editDialog.nameLineEdit->setText(QString::fromStdString(staff.getName()));
		if (staff.getPosition() == "менеджер") {
			editDialog.rBtnManager->setChecked(true);
		}
		else if (staff.getPosition() == "дизайнер") {
			editDialog.rBtnDesigner->setChecked(true);
		}

		if (editDialog.exec()) {
			Staff editStaff;
			editStaff.setId(staff.getId());
			editStaff.setName(editDialog.nameLineEdit->text().toStdString());
			if (editDialog.rBtnDesigner->isChecked()) {
				editStaff.setPosition("дизайнер");
			}
			else if (editDialog.rBtnManager->isChecked()) {
				editStaff.setPosition("менеджер");
			}

			DataBase::editStaff(editStaff);
			setStaffList();
		}
	}
}

void StaffsForm::slot3() {
	//удалить сотрудника

	if (getSelectedStaffId() != -1) {
		DataBase::removeStaff(getSelectedStaffId());
		setStaffList();
	}
}

void StaffsForm::slot5() {
	//выбор менеджера

	editBtn->setEnabled(true);
	deleteBtn->setEnabled(true);
	designersListWidget->clearSelection();
	QListWidgetItem* curItemManagers = managersListWidget->currentItem();
	setSelectedStaffId(curItemManagers->data(Qt::UserRole).toInt());
}

void StaffsForm::slot6() {
	//выбор дизайнера

	editBtn->setEnabled(true);
	deleteBtn->setEnabled(true);
	managersListWidget->clearSelection();
	QListWidgetItem* curItemDesigners = designersListWidget->currentItem();
	setSelectedStaffId(curItemDesigners->data(Qt::UserRole).toInt());
}

void StaffsForm::setSelectedStaffId(int id) {
	StaffsForm::staffId = id;
}

int StaffsForm::getSelectedStaffId() {
	return StaffsForm::staffId;
}
