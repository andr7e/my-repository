#include "desktopitem.h"

#include <QFile>
#include <QHash>
#include <QDebug>
#include <QStringList>

QHash <QString,QString> parseDesktopFormat (const QString &data);

//Load DesktopItem from .desktop file
void DesktopItem::load (const QString &fname)
{
    qDebug () << Q_FUNC_INFO << fname;

    QFile fd(fname);

    if (fd.open(QIODevice::ReadOnly)){
        QString data = fd.readAll();

        QHash <QString,QString> hash = parseDesktopFormat (data);

        setName (hash["Name="]);
        setIcon (hash["Icon="]);
        setPath (hash["Exec="]);
    }

}

/*
Example

[Desktop Entry]
Version=1.0
Type=Application
Name=GIMP Image Editor
GenericName=Image Editor
Comment=Create images and edit photographs
Exec=gimp-2.8 %U
TryExec=gimp-2.8
Icon=gimp
Terminal=false
Categories=Graphics;2DGraphics;RasterGraphics;GTK;
X-GNOME-Bugzilla-Bugzilla=GNOME
X-GNOME-Bugzilla-Product=GIMP
X-GNOME-Bugzilla-Component=General
X-GNOME-Bugzilla-Version=2.8.2
X-GNOME-Bugzilla-OtherBinaries=gimp-2.8
StartupNotify=true
MimeType=application/postscript;application/pdf;
*/

QHash <QString,QString> parseDesktopFormat (const QString &data)
{
    QStringList strList = data.split ("\n");

    qDebug () << Q_FUNC_INFO << strList;

    QStringList keys;
    keys << "Name=" << "Icon=" << "Type=" << "Exec=";

    QHash <QString,QString> hash;

    //look string list
    foreach (QString str, strList)
    {
        if (!str.isEmpty())
        {
            foreach (QString key, keys)
            {
                //key in str?
                if (str.startsWith (key))
                {
                    str.remove(key);

                    qDebug () << Q_FUNC_INFO << str;

                    hash[key] = str;

                    break;
                }
            }
        }
    }

    return hash;
}
