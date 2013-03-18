#ifndef WINDOWSETTINGS_H
#define WINDOWSETTINGS_H

#include <QPoint>
#include <QSize>

class WindowSettings
{
public:
    WindowSettings();

    //Input - default value, output - set to input
    void readWindowSettings (QPoint &pos, QSize &size);

    void writeWindowSettings (const QPoint &pos, const QSize &size);
};

#endif // WINDOWSETTINGS_H
