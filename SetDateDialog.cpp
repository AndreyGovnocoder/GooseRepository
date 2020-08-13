#include "SetDateDialog.h"
#include "qdatetime.h"

SetDateDialog::SetDateDialog(QDate date, QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);
}

SetDateDialog::~SetDateDialog()
{
}
