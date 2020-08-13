#pragma once

#include <QtWidgets/QMainWindow>
#include "Order.h"
#include "ui_MainForm.h"
#include "StaffLogin.h"

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = Q_NULLPTR);
    static void setOrdersTableWidget(QTableWidget*, std::vector<Order>*);
    static void clearPositionsTableWidget(QTableWidget*);
    void setTransparentClientCard();
    void setLogin(StaffLogin);
    StaffLogin getLogin();

private slots:
    void slot1();
    void slot2();
    void slot3();
    void slot4();
    void slot5();
    void slot6();
    void slot7();
    void slot8();
    void slot9();
    void slotCustomMenuRequested(QPoint);
    void slotSetAvailability();

private:
    Ui::MainFormClass ui;
    StaffLogin login;
    void setPositionsTableWidget(int);
    void setClientCard(int);
    void setRemark(int);
    void clearClientCard();
    void clearRemark();
    void setChangesOrderCard(int);
    void clearChangesOrderCard();
};
