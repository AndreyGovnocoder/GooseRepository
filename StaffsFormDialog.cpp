#include "StaffsFormDialog.h"

StaffsFormDialog::StaffsFormDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	setSelectedStaffId(-1);
	setStaffList();
	setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
}

void StaffsFormDialog::setStaffList()
{
	//заполняем listWidget'ы сотрудниками

	designersListWidget->clear();
	managersListWidget->clear();
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
	setSelectedStaffId(-1);

	for (const auto& staff : MainForm::_staffsList)
	{
		if (staff.isActive())
		{
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(staff.getName()));
			item->setData(Qt::UserRole, staff.getId());
			(staff.getPosition() == "менеджер") ? managersListWidget->addItem(item) : designersListWidget->addItem(item);			
		}
	}
}

void StaffsFormDialog::addManagerSlot()
{
	//добавить менеджера

	AddStaffDialog addStaffDialog;
	addStaffDialog.setWindowModality(Qt::WindowModality::ApplicationModal);
	addStaffDialog.setWindowTitle("Менеджер");

	if (addStaffDialog.exec())
	{
		Staff newStaff;
		newStaff.setPosition("менеджер");
		newStaff.setName(addStaffDialog.nameLineEdit->text().toStdString());
		newStaff.setActive(true);
		if (DataBase::addStaff(newStaff))
		{
			newStaff.setId(DataBase::getLastId(DataBase::TABLE_STAFFS));
			MainForm::_staffsList.push_back(std::move(newStaff));
			setStaffList();
		}
		else
			QMessageBox::warning(0, "Ошибка", "Ошибка при добавлении менеджера в базу данных");
	}
}

void StaffsFormDialog::editStaffSlot()
{
	//редактировать сотрудника

	if (getSelectedStaffId() != -1)
	{
		EditStaffDialog editDialog(this);
		editDialog.setWindowTitle("Редактирование сотрудника");
		if (const Staff* staff = MainForm::findStaff(getSelectedStaffId()))
		{
			editDialog.nameLineEdit->setText(QString::fromStdString(staff->getName()));
			if (staff->getPosition() == "менеджер")
				editDialog.rBtnManager->setChecked(true);
			else if (staff->getPosition() == "дизайнер")
				editDialog.rBtnDesigner->setChecked(true);

			if (editDialog.exec())
			{
				Staff editStaff;
				editStaff.setId(staff->getId());
				editStaff.setName(editDialog.nameLineEdit->text().toStdString());
				editStaff.setActive(true);
				if (editDialog.rBtnDesigner->isChecked())
					editStaff.setPosition("дизайнер");
				else if (editDialog.rBtnManager->isChecked())
					editStaff.setPosition("менеджер");
				
				if (DataBase::editStaff(editStaff))
				{
					std::replace_if(MainForm::_staffsList.begin(), MainForm::_staffsList.end(), [&editStaff](const Staff& staff) {return editStaff.getId() == staff.getId(); }, editStaff);
					setStaffList();
				}
				else
					QMessageBox::warning(0, "", "ошибка сохранения изменений " + QString::fromStdString(editStaff.getName()));
			}
		}
	}
}

void StaffsFormDialog::removeStaffSlot()
{
	//удалить сотрудника

	if (getSelectedStaffId() != -1)
	{
		const int removeStaffId = getSelectedStaffId();
		if (MainForm::checkStaffInOrders(removeStaffId))
		{
			if (Staff* editStaff = MainForm::findStaff(removeStaffId))
			{
				editStaff->setActive(false);
				if (DataBase::editStaff(editStaff))
					setStaffList();
				else
					QMessageBox::warning(0, "", "ошибка при удалении сотрудника");
			}
		}
		else
		{
			if (DataBase::removeStaff(removeStaffId))
			{
				auto it = std::remove_if(MainForm::_staffsList.begin(), MainForm::_staffsList.end(), [&removeStaffId](const Staff& staff) {return staff.getId() == removeStaffId; });
				MainForm::_staffsList.erase(it, MainForm::_staffsList.end());
				setStaffList();
			}
			else
				QMessageBox::warning(0, "", "ошибка при удалении сотрудника");
		}		
	}
}

void StaffsFormDialog::addDesignerSlot()
{
	//добавить дизайнера

	AddStaffDialog addStaffDialog;
	addStaffDialog.setWindowModality(Qt::WindowModality::ApplicationModal);
	addStaffDialog.setWindowTitle("Дизайнер");
	if (addStaffDialog.exec())
	{
		Staff newStaff;
		newStaff.setPosition("дизайнер");
		newStaff.setActive(true);
		newStaff.setName(addStaffDialog.nameLineEdit->text().toStdString());
		if (DataBase::addStaff(newStaff))
		{
			newStaff.setId(DataBase::getLastId(DataBase::TABLE_STAFFS));
			MainForm::_staffsList.push_back(std::move(newStaff));
			setStaffList();
		}
		else
			QMessageBox::warning(0, "Ошибка", "Ошибка при добавлении дизайнера в базу данных");
	}
}

void StaffsFormDialog::clickOnManagerSlot()
{
	//выбор менеджера

	editBtn->setEnabled(true);
	deleteBtn->setEnabled(true);
	designersListWidget->clearSelection();
	const int staffId = managersListWidget->currentItem()->data(Qt::UserRole).toInt();
	setSelectedStaffId(staffId);
}

void StaffsFormDialog::clickOnDesignerSlot()
{
	//выбор дизайнера

	editBtn->setEnabled(true);
	deleteBtn->setEnabled(true);
	managersListWidget->clearSelection();
	const int staffId = designersListWidget->currentItem()->data(Qt::UserRole).toInt();
	setSelectedStaffId(staffId);
}
