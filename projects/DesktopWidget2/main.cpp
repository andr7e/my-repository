#include <QApplication>
#include "desktopwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopWidget w;
    w.show();
    
    return a.exec();
}
