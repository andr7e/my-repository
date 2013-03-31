#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ui_mainwindow.h"

#include <libnotifyqwrapper/qsysnotify.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSysNotify obj;
    obj.showMessage("test", "message", QSystemTrayIcon::Information);
}

MainWindow::~MainWindow()
{
    delete ui;
}
