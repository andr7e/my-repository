#define QT_NO_KEYWORDS
#include <QtGui>
#include "qsysnotify.h"

#include <libnotify/notify.h>

//Proxy
Proxy::Proxy (QObject *parent) : QObject(parent){}

Proxy * Proxy::singleton_ = new Proxy();

//QSysNotify
QSysNotify::QSysNotify (QObject *parent) : QObject(parent){}

//libnotify callback
static void notifyCallback (/*NotifyNotification *n, const char *action, gpointer gdata*/)
{
   Proxy::singleton()->callback();
}

void
QSysNotify::
showMessage(const QString &title, const QString &msg, const QString &icon, int msecs, const QString &action){

    if (notify_init (title.toLocal8Bit())){

        NotifyNotification *n = notify_notification_new (title.toLocal8Bit(), msg.toLocal8Bit(), icon.toLocal8Bit());

        if (action.count()) notify_notification_add_action(n, "onclick",  action.toLocal8Bit(), NOTIFY_ACTION_CALLBACK( notifyCallback ), NULL, NULL );

        notify_notification_set_timeout (n, msecs);

        notify_notification_show (n, NULL);

        QObject::connect(Proxy::singleton(), SIGNAL(messageClicked()), SLOT(onClick()));
    }

}

void
QSysNotify::
showMessage(const QString &title, const QString &msg, const QSystemTrayIcon::MessageIcon icon, int msecs, const QString &action){

    QString icon_name;
    switch (icon){
        case QSystemTrayIcon::Information: icon_name = "dialog-information"; break;
        case QSystemTrayIcon::Warning: icon_name = "dialog-warning"; break;
        case QSystemTrayIcon::Critical: icon_name = "dialog-error"; break;

        default: icon_name = ""; // no icon
    }

    showMessage (title, msg, icon_name, msecs, action);
}

void
QSysNotify::
onClick (){
    QObject::disconnect(Proxy::singleton(), SIGNAL(messageClicked()), this, SLOT(onClick()));
    Q_EMIT messageClicked();
}

////////////////////////////////////////////////////////////////////////
/*
1 - set icon name by notify_notification_new (simple, but bad)

2 - if icon not set

GdkPixbuf *pxbuf;

pxbuf = gdk_pixbuf_new_from_file ("/home/andre/1.png", NULL); //gdk_pixbuf_new (GDK_COLORSPACE_RGB, 1, 4, 50, 50);

qDebug () << gdk_pixbuf_get_width(pxbuf) << "x" << gdk_pixbuf_get_height(pxbuf) << gdk_pixbuf_get_bits_per_sample(pxbuf);

notify_notification_set_image_from_pixbuf(n, pxbuf);

3 - QIcon convert to GdkPixbuf (ToDo)

QIcon qicon = QIcon::fromTheme("system-file-manager");
*/


