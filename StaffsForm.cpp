#include "StaffsForm.h"
#include "Staff.h"
#include "DataBase.h"
#include "AddStaffForm.h"
#include "EditStaffDialog.h"

StaffsForm::StaffsForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	setSelectedStaffId(-1);
	setStaffList();
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
}

void StaffsForm::addManagerSlot() 
{
	//добавить менеджера

	AddStaffForm* addStaffDialog = new AddStaffForm(this);
	addStaffDialog->setWindowTitle("Менеджер");

	if (addStaffDialog->exec()) 
	{
		Staff newStaff;
		newStaff.setPosition("менеджер");
		newStaff.setName(addStaffDialog->nameLineEdit->text().toStdString());
		int newId = DataBase::getLastId(DataBase::getTableStaff());
		++newId;
		newStaff.setId(newId);
		DataBase::addStaff(newStaff);
		setStaffList();
	}

	delete addStaffDialog;
}

void StaffsForm::addDesignerSlot()
{
	//добавить дизайнера

	AddStaffForm* addStaffDialog = new AddStaffForm(this);
	addStaffDialog->setWindowTitle("Дизайнер");
	if (addStaffDialog->exec()) 
	{
		Staff newStaff;
		newStaff.setPosition("дизайнер");
		newStaff.setName(addStaffDialog->nameLineEdit->text().toStdString());
		int newId = DataBase::getLastId(DataBase::getTableStaff());
		++newId;
		newStaff.setId(newId);
		DataBase::addStaff(newStaff);
		setStaffList();
	}

	delete addStaffDialog;
}

void StaffsForm::setStaffList() 
{
	//заполняем listWidget'ы сотрудниками

	designersListWidget->clear();
	managersListWidget->clear();
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
	setSelectedStaffId(-1);

	std::vector<Staff> staffList(DataBase::getStaffList());
	for (int i = 0; i < staffList.size(); ++i)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(staffList[i].getName()));
		item->setData(Qt::UserRole, staffList[i].getId());
		if (staffList[i].getPosition() == "менеджер") 
		{
			managersListWidget->addItem(item);
		}
		else 
		{
			designersListWidget->addItem(item);
		}
	}
}

void StaffsForm::editStaffSlot() 
{
	//редактировать сотрудника

	if (getSelectedStaffId() != -1) 
	{
		EditStaffDialog editDialog(this);
		editDialog.setWindowTitle("Редактирование сотрудника");
		Staff staff(DataBase::getStaff(getSelectedStaffId()));

		editDialog.nameLineEdit->setText(QString::fromStdString(staff.getName()));
		if (staff.getPosition() == "менеджер") 
		{
			editDialog.rBtnManager->setChecked(true);
		}
		else if (staff.getPosition() == "дизайнер") 
		{
			editDialog.rBtnDesigner->setChecked(true);
		}

		if (editDialog.exec()) 
		{
			Staff editStaff;
			editStaff.setId(staff.getId());
			editStaff.setName(editDialog.nameLineEdit->text().toStdString());
			if (editDialog.rBtnDesigner->isChecked()) 
			{
				editStaff.setPosition("дизайнер");
			}
			else if (editDialog.rBtnManager->isChecked()) 
			{
				editStaff.setPosition("менеджер");
			}

			DataBase::editStaff(editStaff);
			setStaffList();
		}
	}
}

void StaffsForm::removeStaffSlot() 
{
	//удалить сотрудника

	if (getSelectedStaffId() != -1) 
	{
		DataBase::removeStaff(getSelectedStaffId());
		setStaffList();
	}
}

void StaffsForm::clickOnManagerSlot() 
{
	//выбор менеджера

	editBtn->setEnabled(true);
	deleteBtn->setEnabled(true);
	designersListWidget->clearSelection();
	int staffId = managersListWidget->currentItem()->data(Qt::UserRole).toInt();
	setSelectedStaffId(staffId);
}

void StaffsForm::clickOnDesignerSlot()
{
	//выбор дизайнера

	editBtn->setEnabled(true);
	deleteBtn->setEnabled(true);
	managersListWidget->clearSelection();
	int staffId = designersListWidget->currentItem()->data(Qt::UserRole).toInt();
	setSelectedStaffId(staffId);
}

