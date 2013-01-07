#include <QApplication>
#include "systeminfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SystemInfo w;
    w.show();

    QObject::connect(&w, SIGNAL(close()), &a, SLOT(quit()));
    
    return a.exec();
}
