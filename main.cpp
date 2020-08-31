#include "MainForm.h"
#include <QtWidgets/QApplication>
#include "LoginPassDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    LoginPassDialog* loginDialog = new LoginPassDialog();
    bool launchApp = false;

    if (loginDialog->exec()) 
    {
        launchApp = true;
    }
    else 
    {
        a.quit();
        return 0;
    }  

    if (launchApp)
    {
        MainForm mainForm;
        mainForm.setLogin(loginDialog->getLogin());
        mainForm.setWindowTitle(mainForm.windowTitle() + "  Учетная запись: " + QString::fromStdString(loginDialog->getLogin().getPosition()) + " " + QString::fromStdString(loginDialog->getLogin().getName()));
        delete loginDialog;
        mainForm.show();
        return a.exec();
    }
}
