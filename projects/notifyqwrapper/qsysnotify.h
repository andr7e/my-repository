#ifndef QSYSNOTIFY_H
#define QSYSNOTIFY_H

#include <QObject>
#include <QSystemTrayIcon>

class QSysNotify : public QObject
{
    Q_OBJECT

public:
    QSysNotify(QObject *parent = 0);
    void showMessage (const QString &title, const QString &msg, const QString &icon = 0, int msecs = 10000, const QString &action = 0);
    void showMessage (const QString &title, const QString &msg, const QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int msecs = 10000, const QString &action = 0);

public Q_SLOTS:
    void onClick ();

Q_SIGNALS:
    void messageClicked();
};

#endif // QSYSNOTIFY_H
