#include "MainForm.h"
#include <QtWidgets/QApplication>
#include "LoginPassDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    LoginPassDialog* loginDialog = new LoginPassDialog;
    if (loginDialog->exec()) {
        MainForm mainForm;
        mainForm.setLogin(loginDialog->getLogin());
        mainForm.setWindowTitle(mainForm.windowTitle() + "  Учетная запись: " + loginDialog->getLogin().getQPosition() + " " + loginDialog->getLogin().getQName());
        mainForm.show();
        return a.exec();
    }
    else {
        a.quit();
        return 0;
    }     
}
