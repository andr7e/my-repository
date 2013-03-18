#include "windowsettings.h"
#include <QSettings>
#include <QDebug>

WindowSettings::WindowSettings()
{
}

#define KEY_POS_STRING "/settings/pos"
#define KEY_SIZE_STRING "/settings/size"

void WindowSettings::readWindowSettings (QPoint &pos, QSize &size)
{
    //qDebug () << Q_FUNC_INFO;

    QSettings s;
    pos = s.value (KEY_POS_STRING, pos).toPoint();
    size = s.value (KEY_SIZE_STRING, size).toSize();
}

void WindowSettings::writeWindowSettings (const QPoint &pos, const QSize &size)
{
    //qDebug () << Q_FUNC_INFO;

    QSettings s;
    s.setValue (KEY_POS_STRING, pos);
    s.setValue (KEY_SIZE_STRING, size);
}
