#include "MainForm.h"
#include <QtSql>
#include <QtWidgets/QApplication>
#include "LoginPassDialog.h"
#include <QSqlDatabase>

void delDB(QSqlDatabase* db)
{
    db->close();
    db = nullptr;
    delete db;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 
    LoginPassDialog loginPassDialog;
    bool launchApp = false;
    QSqlDatabase* _db = nullptr;

    _db = new QSqlDatabase();
    if (!QFile("OrderBasePrint_dataBase.db").exists())
    {
        QMessageBox::warning(0, "", "no file db");
    }
    else
    {
        _db = &QSqlDatabase::addDatabase("QSQLITE");
        _db->setHostName("OrderBasePrint_dataBase");
        _db->setDatabaseName("OrderBasePrint_dataBase.db");
        if (!_db->open())
            QMessageBox::warning(0, "", "error open database");        
    }

    loginPassDialog.setWindowTitle("Авторизация");
    if (loginPassDialog.exec())
        launchApp = true;
    else 
    {
        delDB(_db);
        a.quit();        
        return 0;
    }  

    if (launchApp)
    {
        MainForm mainForm(loginPassDialog.getAccountId());
        mainForm.show();
        
        int q = a.exec();

        delDB(_db);
        
        return q;
    }
}

