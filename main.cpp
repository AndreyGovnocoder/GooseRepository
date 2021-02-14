#include "MainForm.h"
#include <QtSql>
#include <QtWidgets/QApplication>
#include "LoginPassDialog.h"
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 
    LoginPassDialog loginPassDialog;
    bool launchApp = false;

    if (!QFile("OrderBasePrint_dataBase.db").exists())
        QMessageBox::warning(0, "", "no file db");
    else
        DataBase::initDatabase();  

    loginPassDialog.setWindowTitle("Авторизация");
    if (loginPassDialog.exec())
        launchApp = true;
    else 
    {
        a.quit();        
        return 0;
    }  

    if (launchApp)
    {
        MainForm mainForm(loginPassDialog.getAccountId());
        mainForm.show();
        
        const int q = a.exec();

        return q;
    }
}

